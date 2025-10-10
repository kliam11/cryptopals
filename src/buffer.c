#include "buffer.h"

static cryptop_errno _buffer_expand(buffer_t buffer);
static cryptop_errno _buffer_compress(buffer_t buffer);

struct buffer_instance_t {
    unsigned char** data;
    size_t* lengths;
    size_t count;
    size_t capacity;
};

buffer_t buffer_create() {
    buffer_t buffer = malloc(sizeof(struct buffer_instance_t));
    if (buffer == NULL) return NULL;

    buffer->data = NULL;
    buffer->lengths = NULL;
    buffer->count = 0;
    buffer->capacity = 0;

    return buffer;
}

void buffer_destroy(buffer_t buffer) {
    if (buffer == NULL) return;

    for (size_t i = 0; i < buffer->count; ++i)
        free(buffer->data[i]);

    free(buffer->data);
    free(buffer->lengths);
    free(buffer);
}

cryptop_errno buffer_add(buffer_t buffer, unsigned char* data, size_t data_l, size_t* loc) {
    if(buffer == NULL || data == NULL || data_l == 0) return CRYPTOP_ERR_NULLPTR;

    if(buffer->count == buffer->capacity) {
        if(_buffer_expand(buffer) == CRYPTOP_ERR_NOMEM) return CRYPTOP_ERR_ALLOC;
    }

    unsigned char* cp = malloc(data_l);
    if(cp == NULL) return CRYPTOP_ERR_ALLOC;
    memcpy(cp, data, data_l);

    buffer->data[buffer->count] = cp;
    buffer->lengths[buffer->count] = data_l;
    buffer->count++;

    if(loc != NULL) *loc = buffer->count-1;

    return CRYPTOP_OK;
}

cryptop_errno buffer_get_count(buffer_t buffer, size_t* count_p) {
    if(buffer == NULL) return CRYPTOP_ERR_NULLPTR;
    *count_p = buffer->count;
    return CRYPTOP_OK;
}

cryptop_errno buffer_get(buffer_t buffer, size_t index, unsigned char** data_p, size_t* data_l) {
    if(buffer == NULL) return CRYPTOP_ERR_NULLPTR;
    if(index >= buffer->count) return CRYPTOP_ERR_OUTOFINDEX;
    *data_p = buffer->data[index];
    *data_l = buffer->lengths[index];
    return CRYPTOP_OK;
}

cryptop_errno buffer_remove(buffer_t buffer, size_t index) {
    if(buffer == NULL) return CRYPTOP_ERR_NULLPTR;
    if(index >= buffer->count) return CRYPTOP_ERR_OUTOFINDEX;

    free(buffer->data[index]);

    for(size_t i=index; i<buffer->count-1; ++i) {
        buffer->data[i] = buffer->data[i+1];
        buffer->lengths[i] = buffer->lengths[i+1];
    }
    buffer->count--;

    if(buffer->count <buffer->capacity/4) {
        _buffer_compress(buffer);
    }

    return CRYPTOP_OK;
}

static cryptop_errno _buffer_expand(buffer_t buffer) {
    size_t new_capacity = (buffer->capacity == 0) ? 8 : buffer->capacity * 2;

    unsigned char **tmp_data = realloc(buffer->data, new_capacity * sizeof(unsigned char *));
    size_t *tmp_lengths = realloc(buffer->lengths, new_capacity * sizeof(size_t));
    if (tmp_data == NULL || tmp_lengths == NULL)
        return CRYPTOP_ERR_NOMEM;

    buffer->data = tmp_data;
    buffer->lengths = tmp_lengths;
    buffer->capacity = new_capacity;

    return CRYPTOP_OK;
}

static cryptop_errno _buffer_compress(buffer_t buffer) {
    size_t new_capacity = buffer->capacity / 2;
    if (new_capacity < buffer->count)
        new_capacity = buffer->count;

    unsigned char **tmp_data = realloc(buffer->data, new_capacity * sizeof(unsigned char *));
    size_t *tmp_lengths = realloc(buffer->lengths, new_capacity * sizeof(size_t));
    if (tmp_data == NULL || tmp_lengths == NULL)
        return CRYPTOP_ERR_NOMEM;

    buffer->data = tmp_data;
    buffer->lengths = tmp_lengths;
    buffer->capacity = new_capacity;
    
    return CRYPTOP_OK;
}