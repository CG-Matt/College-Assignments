#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>

// #define LED_PIN LED_BUILTIN
#define LED_PIN PIN6

#define DOT 250
#define DASH 3 * DOT
#define SPACE 7 * DOT

static const char* message = "MB";

static const char* char_morse_code[] =
{
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--..", // Z
};

const char* CharToMorseCode(char c)
{
    c -= 0x41;

    if(c < 0) return NULL;
    if(c < 26) return char_morse_code[c];

    c -= 0x20;

    if(c < 0) return NULL;
    if(c < 26) return char_morse_code[c];

    return NULL;
}

void PulseLED(size_t ms)
{
    digitalWrite(LED_PIN, HIGH);
    delay(ms);
    digitalWrite(LED_PIN, LOW);
}

void setup()
{
    pinMode(LED_PIN, OUTPUT);
}

void loop()
{
    for(size_t i = 0; i < strlen(message); i++)
    {
        const char* line = CharToMorseCode(message[i]);
        if(!line)
        {
            delay(SPACE);
            delay(DOT); // Time between characters
            continue;
        }
        else
        {
            for(size_t j = 0; j < strlen(line); j++)
            {
                if(line[j] == '.')
                    PulseLED(DOT);
                else // line[j] == '-'
                    PulseLED(DASH);
                delay(DOT); // Time between symbols
            }
        }
        delay(DASH - DOT); // Makes total delay between characters 3 DOTS
    }
}