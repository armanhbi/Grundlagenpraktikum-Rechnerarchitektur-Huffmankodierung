#include "shannonfano.h"

void recursive_encode(uint8_t start_index, uint8_t end_index, Entry *table, size_t length, uint32_t *lookup_table,
                      uint8_t *length_table) {
    int diff = end_index - start_index;
    if (diff <= 1) {
        return;
    }

    if (diff == 2) {
        uint8_t fst_character = table[start_index].character;
        uint8_t snd_character = table[start_index + 1].character;

        if (fst_character == 0 || snd_character == 0) {
            return;
        }

        lookup_table[fst_character] <<= 1;
        length_table[fst_character]++;

        lookup_table[snd_character] <<= 1;
        lookup_table[snd_character]++;
        length_table[snd_character]++;
        return;
    }

    double left_side_adder = 0.0;
    double right_side_adder = 0.0;
    double lsa = 0.0;
    double rsa = 0.0;

    int max_index = -1;
    double max_ratio = 0;

    for (int i = 0; left_side_adder <= right_side_adder; i++) {
        left_side_adder += table[i].frequency;
        right_side_adder = length - left_side_adder;

        double ratio = left_side_adder / right_side_adder;
        if (ratio > 1)
            ratio = ratio - (int) ratio;

        if (ratio > max_ratio) {
            max_ratio = ratio;
            max_index = i + start_index;
            lsa = left_side_adder;
            rsa = right_side_adder;

            if (max_ratio == 1) {
                break;
            }
        }
    }

    for (int i = start_index; i < end_index; i++) {
        uint8_t cur_character = table[i].character;

        if (cur_character == 0) {
            continue;
        }

        lookup_table[cur_character] <<= 1;

        if (i > max_index) {
            lookup_table[cur_character]++;
        }
        length_table[cur_character]++;
    }

    recursive_encode(start_index, max_index + 1, table, lsa, lookup_table, length_table);
    recursive_encode(max_index + 1, end_index, table, rsa, lookup_table, length_table);
}

char *shannonfano_encode(size_t len, const char data[len]) {
    uint16_t freq_table[HEAP_SIZE] = {0}; // create table (same as extended unicode table (8 bits))

    // COUNT OCCURRENCES OF LETTERS

    for (size_t i = 0; i < len; i++) { // Go through input string O(n)
        freq_table[(uint8_t) data[i]] += 1; // increment for every following letter (counting appearance)
    }

    // TRANSLATE TO ENTRIES

    uint8_t internal_index = 0;
    Entry table[HEAP_SIZE] = {0};

    for (uint16_t i = 0; i < HEAP_SIZE; i++) {
        if (freq_table[i] == 0) // if the value in the table is zero
            continue;

        Entry entry = {.character = i, .frequency = freq_table[i]};
        table[internal_index++] = entry;
    }

    // ENTRIES INSERTIONSORT

    for (int i = 1; i < internal_index; i++) {
        Entry tmp = table[i];
        int j = i - 1;

        while (tmp.frequency < table[j].frequency && j >= 0) {
            table[j + 1] = table[j];
            j--;
        }
        table[j + 1] = tmp;
    }

    // HÄUFIGKEITSANALYSE

    print("%sHäufigkeitsanalyse%s\n", CYAN, WHITE);
    for (int i = 0; i < internal_index; i++) {
        print("'%c' kommt %s%d%s mal vor!\n", table[i].character, RED, table[i].frequency, WHITE);
    }

    // RECURSIV CODES ERRECHNEN

    uint8_t length_table[HEAP_SIZE] = {0};
    uint32_t lookup_table[HEAP_SIZE] = {0};

    recursive_encode(0, internal_index, table, len, lookup_table, length_table);

    // DICTIONARY

    print("\n%sDictionary%s\n", CYAN, WHITE);
    for (uint16_t i = 0; i < HEAP_SIZE; i++) { // For every ascii character
        if (length_table[i] != 0) {
            print("'%c' (%d) -> ", i, i);
            print_binary(lookup_table[i], length_table[i]);
            print(" (Länge: %d)", length_table[i]);
            print("\n");
        }
    }
    print("\n");

    char *huffman = calloc(BUF_LENGTH, sizeof(char));

    if (!huffman) {
        return NULL;
    }

    uint32_t huffman_index = 0;

    // DICTIONARY SPEICHERN

    for (uint16_t i = 0; i < HEAP_SIZE; i++) {
        if (length_table[i] != 0) {

        }
    }

    // SHANNONFANO CODE ERZEUGEN UND SPEICHERN

    for (size_t i = 0; i < len; i++) {
        uint32_t code = lookup_table[(uint8_t) data[i]]; // Get huffman code as int
        uint8_t length = length_table[(uint8_t) data[i]]; // Get length of huffman code
        uint32_t mask = 1 << (length - 1); // mask moving from length to the end of the character (right side)

        for (uint32_t i = 0; mask; i++) {
            // If the Huffman Code is too long -> Error => Not really necessary because of check in read_data
            if (huffman_index > BUF_LENGTH) {
                perror("Der Huffman Code würde länger werden als Memory reserviert ist");
                free(huffman);
                return NULL;
            }
            huffman[huffman_index++] = ((code & mask) >> (length - 1 - i)) ? '1' : '0'; // translate character to binary
            mask >>= 1;
        }
    }

    return huffman;
}