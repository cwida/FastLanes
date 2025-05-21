# mk/data.mk — Data & history helpers

# assume $(ACTIVATE) is defined in mk/python.mk
.PHONY: generate_synthetic_data check_fastlanes_result_history time_ctest

generate_synthetic_data: $(ACTIVATE)
	$(call echo_start,Generating synthetic data…)
	$(PIP) install Faker
	cd scripts && PYTHONPATH=$(PWD) ../$(PYTHON) generate_synthetic_data.py \
	  --num-records 5000 \
	  --output ../data/synthetic_users.csv
	$(call echo_done,Synthetic data generated.)

check_fastlanes_result_history: $(ACTIVATE)
	$(call echo_start,Checking CSV history…)
	cd scripts && ../$(PYTHON) check_fastlanes_result_history.py
	$(call echo_done,CSV history check complete.)

time_ctest:
	$(call echo_start,Running ctest with timing…)
	cd cmake-build-release && time ctest --output-on-failure
	$(call echo_done,ctest run complete.)
