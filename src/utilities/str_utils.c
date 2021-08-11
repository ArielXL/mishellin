// stack overflow
char *itoa (int value, char *result, int base){
    // check that the base if valid
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do
    {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while (value);

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';

    while (ptr1 < ptr)
    {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }

    if(result[1] == '\0')
    {
        result[1] = result[0];
        result[0] = '0';
        result[2] = '\0';
    }

    return result;
}
char *path_fixformat(char *path) {
    char *pth_end;
    int slash = 2;
    pth_end = path;
    while(*pth_end != '\0')
        pth_end++;
    while(path != pth_end &&(*pth_end != '/' || slash--))
        pth_end--;

    *pth_end = '~';
    return pth_end;
}