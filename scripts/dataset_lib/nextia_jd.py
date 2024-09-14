from dataset_lib.common import *


class NextiaJD:
    table_list = \
        [
            'all_anonymized_2015_11_2017_03',
            'artists',
            'az',
            'business_licences',
            'Chicago_Crimes_2001_to_2004',
            'Chicago_Crimes_2005_to_2007',
            'Chicago_Crimes_2012_to_2017',
            'comments',
            'Consumer_Complaints',
            'econbiz',
            'eo2',
            'eo3',
            'examiner_date_text',
            'examiner_date_tokens',
            'glassdoor_photos',
            'Homo_sapiens_GRCh38_92',
            'news_week_17aug24',
            'otp',
            'plays',
            'previous_application',
            'property_tax_report',
            'reviews_detailed',
            'reviews_summary',
            'saudi_hourly_weather_data',
            'train_balanced_sarcasm',
            'trainView',
            'us_perm_visas',
            'wowah_data',
            'yellow_tripdata_2019_01'
        ]
    URL = 'https://homepages.cwi.nl/~boncz/NextiaJD/'
    DATA_URL_FILE = "data-urls.txt"
    name = "NextiaJD"

    @staticmethod
    def get_working_dir():
        return os.path.join(nextia_jd_dir_path)

    def get_dir_path(self, table_name):
        return '"FastLanes_Data/{1}/tables/{0}"'.format(table_name, self.name)
