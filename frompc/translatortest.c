#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>
 
static const char * const initial_array[] = {
    "ㄱ", "ㄲ", "ㄴ", "ㄷ", "ㄸ", "ㄹ", "ㅁ", "ㅂ", "ㅃ", "ㅅ",
    "ㅆ", "ㅇ", "ㅈ", "ㅉ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
};
static const char * const medial_array[] = {
    "ㅏ", "ㅐ", "ㅑ", "ㅒ", "ㅓ", "ㅔ", "ㅕ", "ㅖ", "ㅗ", "ㅘ",
    "ㅙ", "ㅚ", "ㅛ", "ㅜ", "ㅝ", "ㅞ", "ㅟ", "ㅠ", "ㅡ", "ㅢ",
    "ㅣ"
};
static const char * const final_array[] = {
      "", "ㄱ", "ㄲ", "ㄳ", "ㄴ", "ㄵ", "ㄶ", "ㄷ", "ㄹ", "ㄺ",
    "ㄻ", "ㄼ", "ㄽ", "ㄾ", "ㄿ", "ㅀ", "ㅁ", "ㅂ", "ㅄ", "ㅅ",
    "ㅆ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"
};
 
#define count_elements_of(array) (sizeof(array)/sizeof(array[0]))
 
static _Bool DecomposeKoreanSyllable(wchar_t code, wchar_t *initial, wchar_t *medial, wchar_t *final){
    const wchar_t num_initial = count_elements_of(initial_array);
    const wchar_t num_medial = count_elements_of(medial_array);
    const wchar_t num_final = count_elements_of(final_array);
    const wchar_t begin = 0xAC00;
    const wchar_t end = begin + num_initial * num_medial * num_final;
 
    if(begin <= code && code < end){
        code -= begin;
        if(final)*final = code % num_final;
        code /= num_final;
        if(medial)*medial = code % num_medial;
        code /= num_medial;
        if(initial)*initial = code;
        return true;
    }
    else return false;
}
 
int main(void){
    char buf[80];
	int i =0;
    setlocale(LC_ALL, "");
    mbtowc(0, 0, 0); // reset
	
 //point A
    while(fgets(buf, sizeof(buf), stdin)){
	buf[0] = 'a';
	printf("printf : %s",&buf[0]);
	size_t buf_offset = 0, buf_len = strlen(buf);
        wchar_t wc;
        int wc_len;
        //Point B
	while((wc_len = mbtowc(&wc, buf + buf_offset, buf_len - buf_offset)) > 0){
            wchar_t initial, medial, final;
            if(DecomposeKoreanSyllable(wc, &initial, &medial, &final)){
                fputs(initial_array[initial], stdout);
                fputs(medial_array[medial], stdout);
                fputs(final_array[final], stdout);
		printf("%d",initial);
            }
            buf_offset += wc_len;
			//point C
        }
   
	}
    putchar('\n');
    return 0;
}