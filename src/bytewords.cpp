//
//  bytewords.cpp
//
//  Copyright © 2020 by Blockchain Commons, LLC
//  Licensed under the "BSD-2-Clause Plus Patent License"
//

#include "bytewords.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <algorithm>

namespace ur {

using namespace std;

static const char* bytewords = "ableacidalsoapexaquaarchatomauntawayaxisbackbaldbarnbeltbetabiasbluebodybragbrewbulbbuzzcalmcashcatschefcityclawcodecolacookcostcruxcurlcuspcyandarkdatadaysdelidicedietdoordowndrawdropdrumdulldutyeacheasyechoedgeepicevenexamexiteyesfactfairfernfigsfilmfishfizzflapflewfluxfoxyfreefrogfuelfundgalagamegeargemsgiftgirlglowgoodgraygrimgurugushgyrohalfhanghardhawkheathelphighhillholyhopehornhutsicedideaidleinchinkyintoirisironitemjadejazzjoinjoltjowljudojugsjumpjunkjurykeepkenokeptkeyskickkilnkingkitekiwiknoblamblavalazyleaflegsliarlimplionlistlogoloudloveluaulucklungmainmanymathmazememomenumeowmildmintmissmonknailnavyneednewsnextnoonnotenumbobeyoboeomitonyxopenovalowlspaidpartpeckplaypluspoempoolposepuffpumapurrquadquizraceramprealredorichroadrockroofrubyruinrunsrustsafesagascarsetssilkskewslotsoapsolosongstubsurfswantacotasktaxitenttiedtimetinytoiltombtoystriptunatwinuglyundouniturgeuservastveryvetovialvibeviewvisavoidvowswallwandwarmwaspwavewaxywebswhatwhenwhizwolfworkyankyawnyellyogayurtzapszerozestzinczonezoom";


static const int16_t _lookup[] = {
    4, 14, 29, 37, -1, -1, 73, -1, 99, -1, -1, 128, -1, -1, -1, 177,
    -1, -1, 194, 217, -1, 230, -1, -1, 248, -1, -1, 20, -1, -1, -1, -1,
    -1, -1, -1, -1, 126, 127, -1, 160, -1, -1, -1, -1, 203, 214, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 253, 1, 11,
    -1, -1, -1, 72, 80, 88, 98, -1, -1, 137, 149, 155, -1, 168, 179, 186,
    -1, 210, -1, 231, 234, -1, -1, -1, 0, 16, 28, 40, 52, 69, 74, 95,
    100, 107, 124, 138, 145, 159, 162, 175, -1, 181, 193, 211, 222, 228, 237, -1,
    -1, 254, -1, -1, 25, -1, -1, -1, -1, 86, -1, -1, -1, 130, -1, -1,
    -1, 176, -1, 188, 204, -1, -1, -1, 243, -1, -1, -1, -1, 18, -1, -1,
    -1, 70, -1, 87, -1, -1, 123, 141, -1, -1, -1, -1, -1, -1, 202, -1,
    -1, -1, -1, -1, -1, -1, 5, -1, 23, -1, 49, 63, 84, 92, 101, -1,
    -1, -1, 144, -1, -1, -1, -1, 185, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, 39, -1, -1, -1, -1, -1, -1, 125, -1, -1, -1, -1, -1,
    -1, -1, -1, 208, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 10, 30, 36, -1, -1, -1, 89, -1, 115, 121, 140,
    152, -1, -1, 170, -1, 187, 197, 207, -1, -1, 244, -1, 245, -1, -1, -1,
    33, 47, -1, 71, 78, 93, -1, 111, -1, -1, -1, 153, 166, 174, -1, 183,
    -1, 213, -1, 227, 233, -1, 247, -1, 6, -1, 22, 46, 55, 62, 82, -1,
    106, -1, -1, -1, -1, -1, -1, 173, -1, -1, -1, -1, -1, -1, 235, -1,
    -1, 255, -1, 12, 35, 43, 54, 60, -1, 96, 105, 109, 122, 134, 142, 158,
    165, -1, -1, 190, 205, 218, -1, -1, 241, -1, 246, -1, 2, -1, -1, -1,
    51, -1, 85, -1, 103, 112, 118, 136, 146, -1, -1, -1, -1, 184, 201, 206,
    220, 226, -1, -1, -1, 251, -1, -1, 34, 45, -1, 65, -1, 91, -1, 114,
    117, 133, -1, -1, -1, -1, -1, 182, 200, 216, -1, -1, 236, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, 59,
    75, -1, -1, -1, -1, 132, -1, -1, -1, 178, -1, -1, 195, -1, 223, -1,
    -1, -1, -1, -1, 9, 15, 24, 38, 57, 61, 76, 97, 104, 113, 120, 131,
    151, 156, 167, 172, -1, 191, 196, 215, -1, 232, 239, -1, -1, 250, 7, 13,
    31, 41, 56, 58, 77, 90, -1, 110, 119, 135, 150, 157, 163, 169, -1, 192,
    199, 209, 221, 224, 240, -1, 249, 252, -1, -1, -1, -1, -1, -1, 83, -1,
    -1, -1, -1, 139, 147, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19, 27, 44,
    -1, 66, 79, -1, -1, -1, -1, -1, 148, -1, -1, -1, -1, -1, 198, -1,
    -1, 229, -1, -1, -1, -1, 3, -1, 32, -1, -1, 67, -1, -1, -1, -1,
    -1, -1, -1, -1, 164, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    8, 17, 26, 48, 50, 68, 81, 94, 102, 116, -1, 129, 143, 154, 161, 171,
    -1, 189, -1, 212, 219, 225, 238, -1, -1, -1, -1, 21, -1, -1, -1, 64,
    -1, -1, -1, 108, -1, -1, -1, -1, -1, -1, 180, -1, -1, -1, -1, -1,
    242, -1, -1, -1
};

static bool decode_word(const string& word, size_t word_len, uint8_t& output) {
    const size_t dim = 26;

    // Sanity check
    if(word.length() != word_len) {
        return false;
    }

    // If the coordinates generated by the first and last letters are out of bounds,
    // or the lookup table contains -1 at the coordinates, then the word is not valid.
    int x = tolower(word[0]) - 'a';
    int y = tolower(word[word_len == 4 ? 3 : 1]) - 'a';
    if(!(0 <= x && x < dim && 0 <= y && y < dim)) {
        return false;
    }
    size_t offset = y * dim + x;
    int16_t value = _lookup[offset];
    if(value == -1) {
        return false;
    }

    // If we're decoding a full four-letter word, verify that the two middle letters are correct.
    if(word_len == 4) {
        const char* byteword = bytewords + value * 4;
        int c1 = tolower(word[1]);
        int c2 = tolower(word[2]);
        if(c1 != byteword[1] || c2 != byteword[2]) {
            return false;
        }
    }

    // Successful decode.
    output = value;
    return true;
}

static const string get_word(uint8_t index) {
    auto p = &bytewords[index * 4];
    return string(p, p + 4);
}

static const string get_minimal_word(uint8_t index) {
    string word;
    word.reserve(2);
    auto p = &bytewords[index * 4];
    word.push_back(*p);
    word.push_back(*(p + 3));
    return word;
}

static const string encode(const ByteVector& buf, const string& separator) {
    auto len = buf.size();
    StringVector words;
    words.reserve(len);
    for(int i = 0; i < len; i++) {
        auto byte = buf[i];
        words.push_back(get_word(byte));
    }
    return join(words, separator);
}

static const ByteVector add_crc(const ByteVector& buf) {
    auto crc_buf = crc32_bytes(buf);
    auto result = buf;
    append(result, crc_buf);
    return result;
}

static const string encode_with_separator(const ByteVector& buf, const string& separator) {
    auto crc_buf = add_crc(buf);
    return encode(crc_buf, separator);
}

static const string encode_minimal(const ByteVector& buf) {
    string result;
    auto crc_buf = add_crc(buf);
    auto len = crc_buf.size();
    for(int i = 0; i < len; i++) {
        auto byte = crc_buf[i];
        result.append(get_minimal_word(byte));
    }
    return result;
}

static const ByteVector _decode(const string& s, char separator, size_t word_len) {
    StringVector words;
    if(word_len == 4) {
        words = split(s, separator);
    } else {
        words = partition(s, 2);
    }
    ByteVector buf;
    buf.reserve(words.size());
    for (const auto &word : words) {
        uint8_t output;
        if (!decode_word(word, word_len, output)) {
            // Failed to decode word
            return ByteVector();
        }
        buf.push_back(output);
    }
    if(buf.size() < 5) {
        return ByteVector();
    }
    auto p = split(buf, buf.size() - 4);
    auto body = p.first;
    auto body_checksum = p.second;
    auto checksum = crc32_bytes(body);
    if(checksum != body_checksum) {
        return ByteVector();
    }

    return body;
}

string Bytewords::encode(style style, const ByteVector& bytes) {
    switch(style) {
        case standard:
            return encode_with_separator(bytes, " ");
        case uri:
            return encode_with_separator(bytes, "-");
        case minimal:
            return encode_minimal(bytes);
        default:
            assert(false);
    }
}

ByteVector Bytewords::decode(style style, const string& string) {
    switch(style) {
        case standard:
            return _decode(string, ' ', 4);
        case uri:
            return _decode(string, '-', 4);
        case minimal:
            return _decode(string, 0, 2);
        default:
            assert(false);
    }
}

}
