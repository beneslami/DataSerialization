#ifndef SENTINEL_H
#define SENTINEL_H

#define SENTINEL_INSERTION_CODE(obj)                              \
{                                                                 \
    if(!obj){                                                     \
      serialize_data(b, "0xFFFFFFFF", strlen("0xFFFFFFFF"));      \
      return;                                                     \
    }                                                             \
}

#define SENTINEL_DETECTION_CODE(b)                                \
{                                                                 \
  char sentinel[11];                                              \
  de_serialize_data(sentinel, b, sizeof(unsigned int));           \
  if(!strcmp(sentinel, "0xFFFFFFFF")) return NULL;                \
  serialize_buffer_skip(b, (-1) * sizeof(unsigned int));          \
}

#endif
