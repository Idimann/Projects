#include "input.h"

#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "settings.h"

static void type(const struct key_bind* bind) {
    struct global_data* data = global_data_get();
    struct settings* set = settings_get();

    char* old = data->lines[data->cursor.y].data;

    ++data->lines[data->cursor.y].size;
    data->lines[data->cursor.y].data = malloc(sizeof(char) * data->lines[data->cursor.y].size);

    if(data->cursor.x)
        memcpy(data->lines[data->cursor.y].data, old, sizeof(char) *
                data->cursor.x);

    memcpy(&(data->lines[data->cursor.y].data[data->cursor.x + 1]),
            &(old[data->cursor.x]), sizeof(char) *
            (data->lines[data->cursor.y].size - data->cursor.x - 1));

    if(old)
        free(old);

    data->lines[data->cursor.y].data[data->cursor.x] = bind->bind[bind->size - 1];
    ++data->cursor.x;
}

static void quit(const struct key_bind* _) {
    struct global_data* data = global_data_get();

    data->running = 0;
}

#define CTRL(x) ((x) & 0x1f)
#define KE(x) (struct key_bind) { .bind = { (#x)[0] }, .size = 1, .func = type }
#define KEQ(x) (struct key_bind) { .bind = { x }, .size = 1, .func = type }

const static struct key_bind binds[] = {
    //Simple typing
    KE(L), KE(M), KE(N), KE(O), KE(P), KE(Q), KE(R), KE(S), KE(T), KE(U), KE(V),
    KE(A), KE(B), KE(C), KE(D), KE(E), KE(F), KE(G), KE(H), KE(I), KE(J), KE(K),
    KE(W), KE(X), KE(Y), KE(Z), KEQ(' '),
    KE(a), KE(b), KE(c), KE(d), KE(e), KE(f), KE(g), KE(h), KE(i), KE(j), KE(k),
    KE(l), KE(m), KE(n), KE(o), KE(p), KE(q), KE(r), KE(s), KE(t), KE(u), KE(v),
    KE(w), KE(x), KE(y), KE(z), KE(0), KE(1), KE(2), KE(3), KE(4), KE(5), KE(6),
    KE(7), KE(8), KE(9), KE(!), KE(@), KE(#), KE($), KE(%), KE(^), KE(*), KEQ('('),
    KEQ(')'), KE(-), KE(_), KE(+), KE(=), KE(`), KE(~), KEQ(','), KE(<), KE(.), 
    KE(>), KE(/), KE(?), KE([), KE(]), KE({), KE(}), KE(;), KE(:), KEQ('\''), 
    KEQ('\"'), KEQ('\\'), KE(|),

    //General
    (struct key_bind) {
        .bind = { CTRL('x'), 'c' },
        .size = 2,
        .func = quit
    },
};

unsigned char input_process(const int* input, unsigned char size) {
    unsigned char found = 0;

    for(size_t i = 0; i < sizeof(binds) / sizeof(struct key_bind); i++) {
        if(binds[i].size < size)
            continue;

        if(binds[i].size == size) {
            if(memcmp(binds[i].bind, input, size * sizeof(int)) == 0) {
                binds[i].func(&(binds[i]));
                found = 0;
                break;
            }

            continue;
        }

        if(memcmp(binds[i].bind, input, size * sizeof(int)) == 0)
            found = 1;
    }

    return found;
}
