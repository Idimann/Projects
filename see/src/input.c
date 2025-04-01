#include "input.h"

#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "globals.h"
#include "settings.h"

static void default_mode(const char* _) {
    struct global_data* data = global_data_get();
    data->current_mode = settings_get()->default_mode;
}

static void switch_mode(const char* input) {
    struct global_data* data = global_data_get();
    data->current_mode = input[0];
}

static void type(const char* input) {
    struct global_data* data = global_data_get();

    char* old = data->lines[data->cursor.y].data;

    ++data->lines[data->cursor.y].size;
    data->lines[data->cursor.y].data = malloc(sizeof(char) * data->lines[data->cursor.y].size);

    if(data->cursor.x)
        memcpy(data->lines[data->cursor.y].data, old, sizeof(char) * data->cursor.x);

    memcpy(&(data->lines[data->cursor.y].data[data->cursor.x + 1]),
            &(old[data->cursor.x]), sizeof(char) *
            (data->lines[data->cursor.y].size - data->cursor.x - 1));

    data->lines[data->cursor.y].data[data->cursor.x] = input[0];
    ++data->cursor.x;

    free(old);
}

static void linebreak(const char* _) {
    struct global_data* data = global_data_get();

    struct buffer* old = data->lines;

    ++data->lines_size;
    data->lines = malloc(sizeof(struct buffer) * data->lines_size);

    if(data->cursor.y)
        memcpy(data->lines, old, sizeof(struct buffer) * data->cursor.y);

    if(data->lines_size > data->cursor.y + 2)
        memcpy(&(data->lines[data->cursor.y + 2]), &(old[data->cursor.y + 1]),
                sizeof(struct buffer) * (data->lines_size - data->cursor.y - 2));

    char* o_Old = old[data->cursor.y].data;
    data->lines[data->cursor.y].size = data->cursor.x + 2;
    data->lines[data->cursor.y].data = malloc(sizeof(char) *
            data->lines[data->cursor.y].size);

    data->lines[data->cursor.y + 1].size = old[data->cursor.y].size - data->cursor.x;
    data->lines[data->cursor.y + 1].data = malloc(sizeof(char) *
            data->lines[data->cursor.y + 1].size);

    if(data->cursor.x)
        memcpy(data->lines[data->cursor.y].data, old[data->cursor.y].data,
                sizeof(char) * data->cursor.x);

    data->lines[data->cursor.y].data[data->lines[data->cursor.y].size - 2] = '\n';
    data->lines[data->cursor.y].data[data->lines[data->cursor.y].size - 1] = '\0';

    memcpy(data->lines[data->cursor.y + 1].data, &(old[data->cursor.y].data[data->cursor.x]),
            sizeof(char) * data->lines[data->cursor.y + 1].size);

    data->cursor.x = 0;
    ++data->cursor.y;

    free(o_Old);
    free(old);
}

static void quit(const char* _) {
    struct global_data* data = global_data_get();

    data->running = 0;
}

#define ZERO_BIND ((struct key_bind) { .bind = {}, .size = 0, .argument = NULL, .func = NULL })
#define CTRL(x) ((x) & 0x1f)
#define KE(x) (struct key_bind){ .bind = { (#x)[0] }, .size = 1, .argument = #x, .func = type }
#define KEQ(x, y) (struct key_bind) { .bind = { x }, .size = 1, .argument = y, .func = type }

#define BIND(fun, siz, ...) (struct key_bind) { \
    .bind = { __VA_ARGS__ }, \
    .size = siz, \
    .argument = NULL, \
    .func = fun \
}

#define ARGS_BIND(fun, arg, siz, ...) (struct key_bind) { \
    .bind = { __VA_ARGS__ }, \
    .size = siz, \
    .argument = arg, \
    .func = fun \
}

const static struct mode typing = {
    .name = '\t',
    .binds = {
        //Actual typing
        KE(L), KE(M), KE(N), KE(O), KE(P), KE(Q), KE(R), KE(S), KE(T), KE(U), KE(V),
        KE(A), KE(B), KE(C), KE(D), KE(E), KE(F), KE(G), KE(H), KE(I), KE(J), KE(K),
        KE(W), KE(X), KE(Y), KE(Z), KEQ(' ', " "),
        KE(a), KE(b), KE(c), KE(d), KE(e), KE(f), KE(g), KE(h), KE(i), KE(j), KE(k),
        KE(l), KE(m), KE(n), KE(o), KE(p), KE(q), KE(r), KE(s), KE(t), KE(u), KE(v),
        KE(w), KE(x), KE(y), KE(z), KE(0), KE(1), KE(2), KE(3), KE(4), KE(5), KE(6),
        KE(7), KE(8), KE(9), KE(!), KE(@), KE(#), KE($), KE(%), KE(^), KE(*),
        KEQ('(', "("), KEQ(')', ")"), KE(-), KE(_), KE(+), KE(=), KE(`), KE(~), KE(|),
        KEQ(',', ","), KE(<), KE(.), KE(>), KE(/), KEQ('?', "?"),
        KEQ('[', "["), KEQ(']', "]"), KEQ('{', "{"), KEQ('}', "}"),
        KE(;), KE(:), KEQ('\'', "\'"), KEQ('\"', "\""), KEQ('\\', "\\"),

        BIND(linebreak, 1, '\n'),

        ZERO_BIND,
    }
};

//Never forget the zero bind
const static struct mode* modes[] = {
    &typing,
};

static unsigned char exec(const int* input, unsigned char size, const struct key_bind* binds) {
    unsigned char found = 0;

    for(size_t i = 0; binds[i].func != ZERO_BIND.func; i++) {
        if(binds[i].size < size)
            continue;

        if(binds[i].size == size) {
            if(memcmp(binds[i].bind, input, size * sizeof(int)) == 0) {
                binds[i].func(binds[i].argument);
                found = 2;
                break;
            }

            continue;
        }

        if(memcmp(binds[i].bind, input, size * sizeof(int)) == 0)
            found = 1;
    }

    return found;
}

unsigned char input_process(const int* input, unsigned char size) {
    struct global_data* data = global_data_get();
    struct settings* set = settings_get();

    const struct key_bind* binds = NULL;
    const struct key_bind* d_binds = NULL;

    if(!data->current_mode)
        data->current_mode = set->default_mode;

    for(size_t i = 0; i < sizeof(modes) / sizeof(struct mode*); i++) {
        if(modes[i]->name == data->current_mode) {
            binds = modes[i]->binds;
            if(d_binds)
                break;
        }

        if(modes[i]->name == set->background_mode) {
            d_binds = modes[i]->binds;
            if(binds)
                break;
        }
    }

    if(!d_binds) {
        set->background_mode = modes[0]->name;
        d_binds = modes[0]->binds;
    }

    if(!binds) {
        data->current_mode = modes[0]->name;
        binds = modes[0]->binds;
    }

    const unsigned char d_exec = exec(input, size, d_binds);

    if(d_exec == 2)
        return 0;

    const unsigned char o_exec = exec(input, size, binds);

    if(o_exec == 2)
        return 0;

    return d_exec;
}
