import json

def check_json_file(file_path, expected_structure):
    with open(file_path, 'r') as f:
        data = json.load(f)

    for key, expected_type in expected_structure.items():
        if key not in data:
            print(f"Missing key: {key}")
            continue

        if isinstance(expected_type, list):
            if not isinstance(data[key], list):
                print(f"Incorrect type for key: {key}. Expected list, got {type(data[key])}")
                continue
            for item in data[key]:
                if not isinstance(item, expected_type[0]):
                    print(f"Incorrect type for item in list {key}. Expected {expected_type[0]}, got {type(item)}")
        else:
            if not isinstance(data[key], expected_type):
                print(f"Incorrect type for key: {key}. Expected {expected_type}, got {type(data[key])}")
                continue

            if isinstance(expected_type, dict):
                check_json_file(data[key], expected_type)

def main():
    config_file_path = "./settings.json"
    config_expected_structure = {
        "scaleOfTime": int,
        "timeSettings": {
            "clientSpawnDelay": int,
            "orderPrepareDelay": int,
            "waiterWalkDelay": int,
            "customerEatDelay": int,
            "customerOrderDelay": int
        },
        "openingTime": int,
        "closingTime": int
    }

    data_file_path = "./menu_file.json"
    data_expected_structure = {
        "menu": [{
            "name": str,
            "price": float
        }],
        "dishes": [{
            "name": str,
            "ingredients": [{
                "name": str,
                "quantity": int
            }]
        }],
        "ingredient_prices_per_100g": [{
            "name": str,
            "price": float
        }]
    }

    check_json_file(config_file_path, config_expected_structure)
    check_json_file(data_file_path, data_expected_structure)

    print("JSON files checked successfully.")

if __name__ == "__main__":
    main()