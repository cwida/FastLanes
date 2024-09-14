from dataset_lib.common import *


class PublicBI:
    table_list = \
        [
            'Arade',  #
            'Bimbo',  #
            'CMSprovider',
            'CityMaxCapita',  #
            'CommonGovernment',
            'Corporations',
            'Eixo',
            'Euro2016',
            'Food',
            'Generico',
            'HashTags',
            'Hatred',
            'IGlocations1',
            # 'IGlocations2',
            # 'IUBLibrary',
            'MLB',
            'MedPayment1',
            # 'MedPayment2',
            'Medicare1',
            # 'Medicare2',
            # 'Medicare3',
            'Motos',
            'MulheresMil',
            'NYC',
            'PanCreactomy1',
            # 'PanCreactomy2',
            'Physicians',
            'Provider',
            'RealEstate1',
            # 'RealEstate2',
            'Redfin1',
            # 'Redfin2',
            # 'Redfin3',
            # 'Redfin4',
            'Rentabilidad',
            'Romance',
            'SalariesFrance',
            'TableroSistemaPenal',
            'Taxpayer',
            'Telco',
            'TrainsUK1',  # we use table 2
            'TrainsUK2',
            'USCensus',
            'Uberlandia',
            'Wins',
            'YaleLanguages'
            #
        ]
    issue_1_list = ["Romance", "Euro2016", "HashTags", "Corporations"]
    issue_2_list = ["TrainsUK1"]
    URL = 'http://www.cwi.nl/~boncz/PublicBIbenchmark/'
    # Example of repo structure
    # .
    # ├── data-urls.txt
    # ├── queries
    # │         └── 2.sql
    # ├── samples
    # │         └── Arade_1.sample.csv
    # └── tables
    # └── Arade_1.table.sql
    DATA_URL_FILE = "data-urls.txt"
    name = "public_bi"

    @staticmethod
    def get_working_dir():
        working_dir = os.path.join(sample_dir_path, PublicBI.name, "tables")
        return working_dir

    @staticmethod
    def get_downloaded_dataset_file_path(dataset, table_n):
        working_dir = PublicBI.get_working_dir()
        path = os.path.join(working_dir, dataset + "_" + str(table_n) + ".csv.bz2")
        return path

    @staticmethod
    def get_decompressed_dataset_file_path(dataset, table_n):
        working_dir = PublicBI.get_working_dir()
        path = os.path.join(working_dir, dataset + "_" + str(table_n) + ".csv")
        return path

    @staticmethod
    def get_sampled_dataset_file_path(dataset, table_n, rg_sz):
        working_dir = PublicBI.get_working_dir()
        path = os.path.join(working_dir, dataset + "_" + str(table_n) + "_" + str(rg_sz) + "_0.csv")
        return path

    @staticmethod
    def get_separated_dataset_file_path(dataset, table_n, col_n):
        working_dir = PublicBI.get_working_dir()
        path = os.path.join(working_dir, dataset + "_" + str(table_n) + "_" + str(col_n) + ".sample.csv")
        return path

    @staticmethod
    def is_valid_file(file_path):
        if os.path.exists(file_path) and os.path.getsize(file_path) > 0:
            return True

    @staticmethod
    def parse_table_urls(dataset):
        working_dir = os.path.join(sample_dir_path, "benchmark")  # maybe broken!
        working_dir = os.path.join(working_dir, dataset)
        data_url_txt = os.path.join(working_dir, "data-urls.txt")

        with open(data_url_txt, 'r') as f:
            table_urls = f.read().splitlines()
            ok("data-urls.txt of dataset: {0}, table_n:{1} has been parsed. table_c: {1}".format(dataset,
                                                                                                 str(len(table_urls))))

            return table_urls

    @staticmethod
    def get_table_number(table_url):
        table_n = re.match(r'.*_(.*).csv.*', table_url).groups()
        return table_n

    @staticmethod
    # for now only table_1
    def get_table_list(dataset):
        return [1]

    @staticmethod
    def get_dataset_list():
        return iter(PublicBI.table_list)

    @staticmethod
    def get_n_table():
        return len(PublicBI.table_list)

    # "/FastLanes_Data/public_bi/tables/Wins/Wins_1/Wins_1.csv",
    @staticmethod
    def get_dir_path(table_name):
        return '"FastLanes_Data/{1}/tables/{0}/{0}_1"'.format(table_name, PublicBI.name)
