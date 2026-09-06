#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    STATE_INIT = 1,
    STATE_ACTIVE = 2,
    STATE_FAULT = 3
}DeviceState;

typedef enum{
    PAYLOAD_TEMP_C = 1,
    PAYLOAD_RPM = 2
}PayloadKind;

typedef union{
    int32_t temperature_c;
    uint32_t rpm;
}PayloadValue; 

typedef struct{
    uint32_t id;
    DeviceState state;
    uint8_t flags;
    PayloadKind payload_kind;
    PayloadValue payload;
}DeviceStatus;

static bool parse_i64(const char *text, int64_t *out_value){
    char *end = NULL;
    intmax_t parsed;
    
    if(text == NULL || out_value == NULL || *text == '\0'){
        return false;
    }
    
    errno = 0;
    parsed = strtoimax(text, &end, 10);
    
    if(errno == ERANGE || end == text || *end != '\0'){
        return false;
    }
    
    if(parsed < INT64_MIN || parsed > INT64_MAX){
        return false;
    }
    
    *out_value = (int64_t)parsed;
    return true;
}

static bool checked_u32(int64_t value, uint32_t *out_value){
    if(out_value == NULL){
        return false;
    }
    
    if(value < 0 || value > UINT32_MAX){
        return false;
    }
    
    *out_value = (uint32_t)value;
    return true;
}

static bool checked_u8(int64_t value, uint8_t *out_value){
    if(out_value == NULL){
        return false;
    }
    
    if(value < 0 || value > UINT8_MAX){
        return false;
    }
    
    *out_value = (uint8_t)value;
    return true;
}

static bool checked_i32(int64_t value, int32_t *out_value){
    if(out_value == NULL){
        return false;
    }
    
    if(value < INT32_MIN || value > INT32_MAX){
        return false;
    }
    
    *out_value = (int32_t)value;
    return true;
}

static bool parse_state(const char *text, DeviceState *out_state){
    if(text == NULL || out_state == NULL){
        return false;
    }
    
    if(strcmp(text, "INIT") == 0){
        *out_state = STATE_INIT;
        return true;
    }
    
    if(strcmp(text, "ACTIVE") == 0){
        *out_state = STATE_ACTIVE;
        return true;
    }
    
    if(strcmp(text, "FAULT") == 0){
        *out_state = STATE_FAULT;
        return true;
    }
    return false;
}

static bool parse_payload_kind(const char *text, PayloadKind *out_kind){
    if(text == NULL || out_kind == NULL){
        return false;
    }
    
    if(strcmp(text, "temp") == 0){
        *out_kind = PAYLOAD_TEMP_C;
        return true;
    }
    
    if(strcmp(text, "rpm") == 0){
        *out_kind = PAYLOAD_RPM;
        return true;
    }
    
    return false;
}

static bool make_status(uint32_t id, DeviceState state, uint8_t flags, PayloadKind kind, int64_t raw_payload, DeviceStatus *out){
    DeviceStatus candidate = {0};
    
    if(out == NULL){
        return false;
    }
    
    candidate.id = id;
    candidate.state = state;
    candidate.flags = flags;
    candidate.payload_kind = kind;
    
    if(kind == PAYLOAD_TEMP_C){
        if(!checked_i32(raw_payload, &candidate.payload.temperature_c)){
            return false;
        }
    }else if(kind == PAYLOAD_RPM){
        if(!checked_u32(raw_payload, &candidate.payload.rpm)){
            return false;
        }
    }else{
        return false;
    }
    
    *out = candidate;
    return true;
}

static const char *state_name(DeviceState state){
    switch(state){
        case STATE_INIT:
            return "INIT";
        case STATE_ACTIVE:
            return "ACTIVE";
        case STATE_FAULT:
            return "FAULT";
        default:
            return "UNKNOWN";
    }
}

static void print_status(const DeviceStatus *record){
    if(record == NULL){
        return;
    }
    
    printf("record id=%"PRIu32
    " state=%s"
    " flags=%" PRIu8,
    record->id,
    state_name(record->state),
    record->flags);
    
    if(record->payload_kind == PAYLOAD_TEMP_C){
        printf(" kind=TEMP_C value=%"PRId32 "\n",
            record->payload.temperature_c);
    }else if(record->payload_kind == PAYLOAD_RPM){
        printf(" kind=RPM value=%"PRIu32 "\n",
            record->payload.rpm);
    }
}

int main(int argc, char **argv){
    DeviceStatus record;

    int64_t raw_id;
    int64_t raw_flags;
    int64_t raw_payload;

    uint32_t id;
    uint8_t flags;

    DeviceState state;
    PayloadKind payload_kind;
    
    if(argc != 6){
        fputs(
            "USAGE: device_status <id> <state> <flags> "
            "<temp|rpm> <value>\n",
            stderr
        );

        return 2;
    }
    
    if(!parse_i64(argv[1], &raw_id) || !checked_u32(raw_id, &id)){
        fputs("ERROR invalid id\n", stderr);
        return 2;
    }
    
    if (!parse_state(argv[2], &state)){
        fputs("ERROR invalid state\n", stderr);
        return 2;
    }
    
    if (!parse_i64(argv[3], &raw_flags) || !checked_u8(raw_flags, &flags)){
        fputs("ERROR invalid flags\n", stderr);
        return 2;
    }
    
    if (!parse_payload_kind(argv[4], &payload_kind)){
        fputs("ERROR invalid payload type\n", stderr);
        return 2;
    }
    
    if (!parse_i64(argv[5], &raw_payload)){
        fputs("ERROR invalid payload value\n", stderr);
        return 2;
    }

    if (!make_status(id, state, flags, payload_kind, raw_payload, &record)){
        fputs("ERROR payload value outside allowed range\n",
              stderr);

        return 2;
    }
    
    print_status(&record);
    
    return 0;
}