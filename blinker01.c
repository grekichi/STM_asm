
void PUT32(unsigned int, unsigned int);
unsigned int GET32(unsigned int);
void dummy(unsigned int);

#define GPIOABASE 0x40010800  // GPIO A を使う
#define RCCBASE 0x40021000

int notmain(void)
{
    unsigned int ra;
    unsigned int rx;

    ra = GET32(RCCBASE + 0x18);  // RCC_APB2ENR(APB2 ペリフェラルクロック有効レジスタ) set
    ra |= 1 << 2;  // enable port A
    PUT32(RCCBASE + 0x18, ra);
    // config
    ra = GET32(GPIOABASE + 0x00);  // GPIOA_CRL(ポート設定下位レジスタ) set
    ra &= ~(3 << 20);   // PA5モードビット 00設定 -> 入力モード（*一旦リセット）＊LD2(LED)はPA5に接続されているため
    ra |= 1 << 20;      // PA5モードビット 01設定 -> 出力モード最大速度10MHz
    ra &= ~(3 << 22);   // PA5設定ビット 00設定 -> 汎用出力プッシュプル
    ra |= 0 << 22;      // PA5設定ビット 00設定 -> 同上
    PUT32(GPIOABASE + 0x00, ra);

    for (rx = 0;; rx++)
    {
        PUT32(GPIOABASE + 0x10, 1 << (5 + 0));  // PA5のポートビットをセット
        for (ra = 0; ra < 200000; ra++)
        {
            dummy(ra);
        }
        PUT32(GPIOABASE + 0x10, 1 << (5 + 16));  // PA5のポートビットをリセット
        for (ra = 0; ra < 200000; ra++)
        {
            dummy(ra);
        }
    }
    return 0;
}
