format:
	@echo "Formating"
	python3 scripts/run-clang-format.py -r example include src benchmark test data/include -i --exclude include/fls/json/nlohmann

generate_dataset_headers:
	cd scripts; python3 generate_dataset_headers.py

yaml_to_json:
	cd scripts; python3 yaml_to_json.py
