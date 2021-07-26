#include <cpu/cpu.h>
#include <utils.h>

#define FEATURE_GRANULARITY 64
uint64_t features[10] = {0};


static boolean check_5_page_support()
{

    uint64_t cr4 = CR(4, 0, READ);

    if(_set_bit_check(cr4, 12))
        return true;
    else    
        return false;   
}

static void feature_setter(uint64_t feature_index, boolean (*feature_check_function)())
{
    uint64_t feature_group = feature_index / FEATURE_GRANULARITY;
    uint8_t feature_bit = feature_index % FEATURE_GRANULARITY;
    if(feature_check_function())
        _bit_set(features[feature_group], feature_bit);
    else    
        _bit_clear(features[feature_group], feature_bit);
}

void feature_enumerate()
{
    feature_setter(PAGING_LEVEL_5, check_5_page_support);

}
boolean feature_check(uint64_t feature_index)
{
    uint64_t feature_group = feature_index / FEATURE_GRANULARITY;
    uint8_t feature_bit = feature_index % FEATURE_GRANULARITY;

    if(_set_bit_check(features[feature_group], feature_bit))
        return true;
    else    
        return false;
}