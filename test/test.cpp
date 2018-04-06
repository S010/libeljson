/*
 * Copyright (c) 2012 Sviatoslav Chagaev <sviatoslav.chagaev@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <iostream>
#include <string>
#include <fstream>

#include <json.hpp>

#define ERROR(msg) \
    do { \
        std::cerr << __func__ << "(): " msg << std::endl; \
        exit(1); \
    } while(0)

#define ASSERT(expr) \
    do { \
        if (!(expr)) { \
            ERROR("expression is false: " #expr); \
        } \
    } while (0)

static std::string dir_name(const std::string& s);
static void        test_large_file(const std::string& path);
static void        test_vctor();

int main(int, char **argv) {
    test_large_file(dir_name(*argv) + "/big.json");
    test_vctor();

    return 0;
}

static std::string dir_name(const std::string& s) {
    auto pos = s.rfind('/');

    if (pos == std::string::npos || pos == 0)
        return ".";
    else
        return s.substr(0, pos);
}

static void test_large_file(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        std::cerr << __func__ << "(): " << path << ": failed to open" << std::endl;
        exit(1);
    }
    std::string line, buf;
    while (std::getline(in, line))
        buf.append(line);
    in.close();
    json::value val(json::parse(buf));
    ASSERT("aegwynn" == val["realm"]["slug"]);
    json::value &auc = val["alliance"]["auctions"][1];
    ASSERT(auc["item"] == 3486);
    ASSERT(auc["owner"] == "Addere");
}

static void test_vctor() {
    json::object obj {
        "key1", 123,
        "key2", 42.42,
        "key3", true,
        "key4", false,
        "key5", json::array {
            123,
            444,
            555,
            json::object {
                "aaa", true,
                "bbb", false,
                "ccc", 42,
                "ddd", 1.0/9.0,
                "eee", json::value(),
                "fff", json::array {
                    "some text",
                    42,
                    3.0/9.0,
                    true,
                    false,
                    json::value(),
                },
            },
        },
        "key6", "ElJson",
        "key7", "Variadic templates"
    };

    std::string s(obj.str());

    json::value obj2(json::parse(s));

    ASSERT(obj["key1"] == 123);
    ASSERT(obj["key6"] == "ElJson");
    ASSERT(obj == obj2);
    ASSERT(obj.str() == obj2.str());
}

