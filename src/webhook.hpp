#pragma once

#include "utils//curlpost.hpp"

#include "json/json.hpp"

using json = nlohmann::json;

struct discord_webhook {
    std::string url;
    std::string name;
    std::string avatar;
    std::string message;
};

static bool send_webhook(struct discord_webhook &webhook, std::string &response) {
    std::vector<std::string> chunks;

    size_t length = webhook.message.length();
    for (size_t i = 0; i < length; i += 2000) {
        chunks.push_back(webhook.message.substr(i, 2000));
    }

    json original_json;
    original_json["username"] = webhook.name;
    if (!webhook.avatar.empty()) {
        original_json["avatar_url"] = webhook.avatar;
    }

    if (chunks.size() == 0) {
        return false;
    }

    std::vector<int> return_codes;

    for (const std::string &message : chunks) {

        json copied_json = original_json;
        copied_json["content"] = message;

        std::string post_data = copied_json.dump();

        std::vector<std::string> headers = { "Content-Type: application/json" };

        if (curl_post(webhook.url, headers, post_data, response)) {
            return_codes.push_back(true);
        }
        else {
            return_codes.push_back(false);
        }
    }

    for (const int &code : return_codes) {
        if (code != true) {
            return false;
        }
    }

    return true;
}