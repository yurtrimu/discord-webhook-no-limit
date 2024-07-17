#include "webhook.hpp"

int main()
{
    curl_global_init(CURL_GLOBAL_ALL);

    struct discord_webhook webhook;
    webhook.avatar = "AVATAR_URL";
    webhook.name = "USERNAME";
    webhook.url = "URL";
    webhook.message = "MESSAGE";

    std::string response;

    if (send_webhook(webhook, response)) {
        printf("Webhook successfully sent %zu length of data.\n", webhook.message.length());
    }

    curl_global_cleanup();
}