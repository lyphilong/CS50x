#include <stdio.h>
#include <cs50.h>
#include <string.h>

int countWord(string text);
int countSentence(string text);
int countLetter(string text);
int roundIndex(float index);

int main(void)
{
    string text = get_string("Text: ");

    float word = countWord(text);
    float sentence = countSentence(text);
    float letters = countLetter(text);

    float L = (letters / word) * 100;
    float S = (sentence / word) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;

    /*
        printf("%f letter(s)\n", letters);
        printf("%f word(s)\n", word);
        printf("%f sentence(s)\n", sentence);
    */

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", roundIndex(index));
    }
}

int countWord(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    return (count + 1);

}

int countSentence(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int countLetter(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (('a' <= text[i] && text[i] <= 'z') || ('A' <= text[i] && text[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

int roundIndex(float index)
{
    int tmp = (int) index;
    float decimal = index - tmp;
    if (decimal > 0.5)
    {
        return (tmp + 1);
    }
    else
    {
        return tmp;
    }
}