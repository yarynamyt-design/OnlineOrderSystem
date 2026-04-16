#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

struct Product {
    string name;
    double price;
    int quantity;

    json to_json() const {
        return json{ {"name", name}, {"price", price}, {"quantity", quantity} };
    }

    static Product from_json(const json& j) {
        return { j.at("name"), j.at("price"), j.at("quantity") };
    }
};