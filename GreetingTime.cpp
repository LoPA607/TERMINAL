#define CURL_STATICLIB
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string.h>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <format>
#include <cctype>
#include<bits/stdc++.h>
#pragma warning(disable : 4996)
using namespace std;

#define MAX_LENGTH 256
string buffer;
string user_city;

using json = nlohmann::json;
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append((char*)contents, total_size);
    return total_size;
}

void cur_temp() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        ifstream file;
        file.open("cnf.txt");
        getline(file, buffer, '\n'); 
        buffer[0] = toupper(buffer[0]);
        file.close();

        user_city = "http://api.weatherstack.com/current?access_key=42594ca09cb15c1a8c6ecfd71b6ab00e&query="+ buffer +",%20India";
        const char* api_url = user_city.c_str();
        

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_setopt(curl, CURLOPT_URL, api_url);

        res = curl_easy_perform(curl);
        json data = json::parse(response);

        if (res != CURLE_OK)
            fprintf(stderr, "Temprature request failed \ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            std::cout << "\n" << buffer << ",India" << "\n";
            std::cout << "TEMPERATURE: " << data["current"]["temperature"] << " Celsius\n";
            std::cout << "HUMIDITY: " << data["current"]["humidity"] << "%\n";
            std::cout << "WIND_SPEED: " << data["current"]["wind_speed"] << "km/h\n";
            std::cout << "WEATHER: " << data["current"]["weather_descriptions"][0];

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

}

int one_line(int poss) {
    int line_num = 0;
    srand(time(0));
    ifstream file;
    if (poss == 1) {
        file.open("Mo.txt");
    }
    else if (poss == 2) {
        file.open("Af.txt");
    }
    else {
        file.open("Ev.txt");
    }
    while (getline(file, buffer, '\n')) {
        if (buffer.find('#') != -1) {
            break;
        }
        line_num++;
    }
    int num = (rand() % (line_num - 1 + 1)) + 1;
    file.seekg(0, ios::beg);
    ostringstream out;
    out << num << "-";
    while (getline(file, buffer, '\n')) {
        if (buffer.find(out.str()) != -1) {
            break;
        }
    }
    num = floor(log10(num)) + 1;;
    cout << buffer.substr(num + 1);
    file.close();
    return 0;
}
int calculator(int num1, int num2, char op) {
    int result;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            result = num1 / num2;
            break;
        default:
            cout << "Invalid operator";
            return 0;
    }
    return result;
}
void getNewsHeadlines() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        const char* api_url = "https://newsapi.org/v2/top-headlines?country=us&apiKey=YOUR_API_KEY";

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_setopt(curl, CURLOPT_URL, api_url);

        res = curl_easy_perform(curl);
        json data = json::parse(response);

        if (res != CURLE_OK)
            fprintf(stderr, "News request failed \ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else {
            std::cout << "\nNews Headlines:\n";
            for (const auto& article : data["articles"]) {
                std::cout << "Title: " << article["title"] << "\n";
                std::cout << "Source: " << article["source"]["name"] << "\n";
                std::cout << "Description: " << article["description"] << "\n";
                std::cout << "URL: " << article["url"] << "\n";
                std::cout << "-----------------------------------\n";
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
#include <chrono>
void setReminder(const std::string& reminder, int minutes) {
    std::this_thread::sleep_for(std::chrono::minutes(minutes));
    std::cout << "Reminder: " << reminder << std::endl;
}
void searchLocalFiles(const std::string& keyword) {
    std::string path = "/home/lopamudra/Documents/VS CODE/Open Source/TERMINAL";
    std::string command = "grep -r -i \"" + keyword + "\" " + path;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        std::cout << "Error executing command." << std::endl;
        return;
    }

    char buffer[MAX_LENGTH];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;
    }

    pclose(pipe);
}

void random_joke() {
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        const char* api_url = "https://news.google.com/home?hl=en-IN&gl=IN&ceid=IN:en";

        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        curl_easy_setopt(curl, CURLOPT_URL, api_url);

        res = curl_easy_perform(curl);
        json data = json::parse(response);

        if (res != CURLE_OK)
            fprintf(stderr, "Joke request failed \ncurl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else {
            std::cout << "\nRandom Joke:\n";
            std::cout << "Category: " << data["type"] << "\n";
            std::cout << "Setup: " << data["setup"] << "\n";
            std::cout << "Punchline: " << data["punchline"] << "\n";
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}
int main() {
    char greet[20];
    time_t now = time(0);
    struct tm* ltm = localtime(&now);
    //int hour = 9;
    int hour = ltm->tm_hour;
    const char* message[5] = { "Morning", "Afternoon", "Evening", "Night", "MidNight" };
    if (hour >= 5 && hour < 12) {
        strcpy(greet, message[0]);
        printf("\nHello, Good %s\nHave a Nice Day!!", greet);
        printf("\nMotivational Quote: ");
        one_line(1);//printing the quote
    }
    else if (hour >= 12 && hour < 17) {
        strcpy(greet, message[1]);
        printf("\nHi, Good %s\nHave a Nice Day!!", greet);
        printf("\nMotivational Quote: ");
        one_line(2);//printing fact

    }
    else if (hour >= 17 && hour < 21) {
        strcpy(greet, message[2]);
        printf("\nHi, It's a Lovely %s\nHave a Nice Day!!", greet);
        printf("\nMotivational Quote: ");
        one_line(3);//printing life hack
    }
    else if (hour >= 21 && hour < 24) {
        strcpy(greet, message[3]);
        printf("\nHello, Good %s\nHave a Sweet Dream and Take Care!!", greet);
    }
    else {
        strcpy(greet, message[4]);
        printf("\nHi, It's %s\nHave a Peaceful Sleep!!", greet);
    }
    cur_temp();
    cout << "\n\n";
    if(cin>>"Calculator"){
        cout << "Enter the first number: ";
        int num1;
        cin >> num1;
        cout << "Enter the operator: ";
        char op;
        cin >> op;
        cout << "Enter the second number: ";
        int num2;
        cin >> num2;
        cout << "Result: " << calculator(num1, num2, op);
    }
    if(cin>>"Reminder"){
        std::string reminder;
        int minutes;
        std::cout << "Enter reminder: ";
        std::cin.ignore();
        std::getline(std::cin, reminder);
        std::cout << "Enter time in minutes: ";
        std::cin >> minutes;
        std::thread reminderThread(setReminder, reminder, minutes);
        reminderThread.detach();
    }
    if(cin>>"Joke"){
        random_joke();
    }
    if(cin>>"News"){
        getNewsHeadlines();
    }
    if(cin>>"Search"){
        std::string keyword;
        std::cout << "Enter keyword to search: ";
        std::cin.ignore();
        std::getline(std::cin, keyword);
        searchLocalFiles(keyword);
    }
    return 0;
}
