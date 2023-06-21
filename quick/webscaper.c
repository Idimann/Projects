#include <curl/curl.h>
#include <tidy.h>
#include <tidybuffio.h>
#include <stdio.h>
#include <stdlib.h>

uint write_cb(char *in, uint size, uint nmemb, TidyBuffer *out)
{
    uint r;
    r = size * nmemb;
    tidyBufAppend(out, in, r);
    return r;
}

FILE* file;

/* Traverse the document tree */
void dumpNode(TidyDoc doc, TidyNode tnod, int indent)
{
    TidyNode child;
    for(child = tidyGetChild(tnod); child; child = tidyGetNext(child) ) {
        ctmbstr name = tidyNodeGetName(child);
        if(name) {
            /* if it has a name, then it's an HTML tag ... */
            TidyAttr attr;
            fprintf(file, "%*.*s%s ", indent, indent, "<", name);
            /* walk the attribute list */
            for(attr = tidyAttrFirst(child); attr; attr = tidyAttrNext(attr) ) {
                fprintf(file, "%s", tidyAttrName(attr));
                tidyAttrValue(attr)?fprintf(file, "=\"%s\" ",
                        tidyAttrValue(attr)):fprintf(file, " ");
            }
            fprintf(file, ">\n");
        }
        else {
            /* if it does not have a name, then it's probably text, cdata, etc... */
            TidyBuffer buf;
            tidyBufInit(&buf);
            tidyNodeGetText(doc, child, &buf);
            fprintf(file, "%*.*s\n", indent, indent, buf.bp?(char *)buf.bp:"");
            tidyBufFree(&buf);
        }
        dumpNode(doc, child, indent + 4); /* recursive */
    }
}

int main(int argc, char* argv[]) {

    CURL *curl;
    TidyDoc tdoc;
    TidyBuffer tbuffer;
    TidyBuffer ebuffer;

    int err;

    file = fopen(argv[2], "w+");

    if(argc < 3) {
        printf("Usage: %s <URL> <Filename>", argv[0]);
        return 1;
    }
    
    const char* pageName = argv[2];

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
 
    /* set URL to get here */
    curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
    /* Switch on full protocol/debug output while testing */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    /* disable progress meter, set to 0L to enable it */
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    /* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);

    tdoc = tidyCreate();
    tidyOptSetBool(tdoc, TidyForceOutput, yes); /* try harder */
    tidyOptSetInt(tdoc, TidyWrapLen, 4096);
    tidySetErrorBuffer(tdoc, &ebuffer);
    tidyBufInit(&tbuffer);

    /* write the page body to this file handle */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &tbuffer);
    
    err = curl_easy_perform(curl);
    if(!err) {
        err = tidyParseBuffer(tdoc, &tbuffer);
        if(err >= 0) {
            err = tidyCleanAndRepair(tdoc);
            if(err >= 0) {
                err = tidyRunDiagnostics(tdoc);
                if(err >= 0) {
                    dumpNode(tdoc, tidyGetRoot(tdoc), 0);
                    printf("%s\n", ebuffer.bp);
                }
            }
        }
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl);
    tidyBufFree(&tbuffer);
    tidyBufFree(&ebuffer);
    tidyRelease(tdoc);

    curl_global_cleanup();

    return err;
}
