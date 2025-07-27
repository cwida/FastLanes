# ────────────────────────────────────────────────────────
# |                      FastLanes                       |
# ────────────────────────────────────────────────────────
# scripts/public_bi.py
# ────────────────────────────────────────────────────────
import os
import re

arade = "Arade"
bimbo = "Bimbo"
cms_provider = "CMSprovider"
city_max_capita = "CityMaxCapita"
common_government = "CommonGovernment"
corporations = "Corporations"
eixo = "Eixo"
euro_2016 = "Euro2016"
food = "Food"
generico = "Generico"
hash_tags = "HashTags"
hatred = "Hatred"
ig_locations_1 = "IGlocations1"
mlb = "MLB"
med_payment_1 = "MedPayment1"
medicare_1 = "Medicare1"
motos = "Motos"
mulheres_mil = "MulheresMil"
nyc = "NYC"
pancreactomy_1 = "PanCreactomy1"
physicians = "Physicians"
provider = "Provider"
real_estate_1 = "RealEstate1"
redfin_1 = "Redfin1"
rentabilidad = "Rentabilidad"
romance = "Romance"
salaries_france = "SalariesFrance"
tablero_sistema_penal = "TableroSistemaPenal"
taxpayer = "Taxpayer"
telco = "Telco"
trains_uk_1 = "TrainsUK1"
trains_uk_2 = "TrainsUK2"
us_census = "USCensus"
uberlandia = "Uberlandia"
wins = "Wins"
yale_languages = "YaleLanguages"


class PublicBI:
    table_list = [
        'Arade', 'Bimbo', 'CMSprovider', 'CityMaxCapita', 'CommonGovernment',
        'Corporations', 'Eixo', 'Euro2016', 'Food', 'Generico', 'HashTags',
        'Hatred', 'IGlocations1', 'MLB', 'MedPayment1', 'Medicare1',
        'Motos', 'MulheresMil', 'NYC', 'PanCreactomy1', 'Physicians',
        'Provider', 'RealEstate1', 'Redfin1', 'Rentabilidad', 'Romance',
        'SalariesFrance', 'TableroSistemaPenal', 'Taxpayer', 'Telco',
        'TrainsUK1', 'TrainsUK2', 'USCensus', 'Uberlandia', 'Wins',
        'YaleLanguages'
    ]

    issue_1_list = ['Romance', 'Euro2016', 'HashTags', 'Corporations']
    issue_2_list = ['TrainsUK1']

    base_url = 'http://www.cwi.nl/~boncz/PublicBIbenchmark/'
    data_url_file = 'data-urls.txt'
    name = 'public_bi'

    @staticmethod
    def get_working_dir():
        """Get the directory path where the tables are located."""
        return os.path.join(sample_dir_path, PublicBI.name, 'tables')

    @staticmethod
    def get_downloaded_dataset_file_path(dataset, table_n):
        """Get the path to the downloaded (compressed) dataset."""
        return os.path.join(
            PublicBI.get_working_dir(),
            f"{dataset}_{table_n}.csv.bz2"
        )

    @staticmethod
    def get_decompressed_dataset_file_path(dataset, table_n):
        """Get the path to the decompressed dataset."""
        return os.path.join(
            PublicBI.get_working_dir(),
            f"{dataset}_{table_n}.csv"
        )

    @staticmethod
    def get_sampled_dataset_file_path(dataset, table_n, rg_sz):
        """Get the path to the sampled dataset."""
        return os.path.join(
            PublicBI.get_working_dir(),
            f"{dataset}_{table_n}_{rg_sz}_0.csv"
        )

    @staticmethod
    def get_separated_dataset_file_path(dataset, table_n, col_n):
        """Get the path to the separated dataset."""
        return os.path.join(
            PublicBI.get_working_dir(),
            f"{dataset}_{table_n}_{col_n}.sample.csv"
        )

    @staticmethod
    def is_valid_file(file_path):
        """Check if the file exists and is non-empty."""
        return os.path.exists(file_path) and os.path.getsize(file_path) > 0

    @staticmethod
    def parse_table_urls(dataset):
        """Parse table URLs from the dataset's `data-urls.txt` file."""
        working_dir = os.path.join(sample_dir_path, "benchmark", dataset)
        data_url_txt = os.path.join(working_dir, PublicBI.data_url_file)

        with open(data_url_txt, 'r') as f:
            table_urls = f.read().splitlines()
            print(f"Parsed {len(table_urls)} URLs for dataset: {dataset}")
            return table_urls

    @staticmethod
    def get_table_number(table_url):
        """Extract the table number from the table URL."""
        match = re.match(r'.*_(.*).csv.*', table_url)
        return match.group(1) if match else None

    @staticmethod
    def get_table_list(dataset):
        """Return a list of table numbers (currently only supports table 1)."""
        return [1]

    @staticmethod
    def get_dataset_list():
        """Return an iterator over all tables in the `table_list`."""
        return iter(PublicBI.table_list)

    @staticmethod
    def get_n_table():
        """Return the total number of tables."""
        return len(PublicBI.table_list)

    @staticmethod
    def get_dir_path(table_name):
        """Get the directory path for a given table."""
        return os.path.join('FastLanes_Data', PublicBI.name, 'tables', table_name, f"{table_name}_1")

    @staticmethod
    def get_file_path(table_name):
        """Get the file path for a given table."""
        subfolder = f"{table_name}_2" if table_name == "TrainsUK1" else f"{table_name}_1"
        return os.path.join(
            '/Users/azim/CLionProjects/temp/cmake-build-debug/_deps/data-src/',
            PublicBI.name,
            'tables',
            table_name,
            subfolder,
            f"{table_name}_1.csv"
        )

    @staticmethod
    def get_schema_file_path(table_name):
        """Get the file path for a given table."""
        subfolder = f"{table_name}_2" if table_name == "TrainsUK1" else f"{table_name}_1"
        return os.path.join(
            '/Users/azim/CLionProjects/temp/cmake-build-debug/_deps/data-src/',
            PublicBI.name,
            'tables',
            table_name,
            subfolder,
            "schema.json"
        )
