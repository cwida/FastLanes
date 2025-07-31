import pandas as pd

def truncate_csv(input_file, output_file, num_lines):
    df = pd.read_csv(input_file, nrows=num_lines)
    df.to_csv(output_file, index=False)

# 示例用法：
x = 65535  # 想保留的行数
all_datasets = ["AMPds","Computer_Monitor", "Linear_Road", "Smart_Grid", "Weather_Forcast"]
all_filenames = ["amp", "cm", "lr", "sg", "wf"]
for i in range(len(all_datasets)):
    dataset = all_datasets[i] # 数据集名称
    filename = all_filenames[all_datasets.index(dataset)]
    input_csv = "/home/tangyuxin/cleanFastlanes/FastLanes/data/_TimeSeries/tables/"+dataset+"/"+filename+".csv"
    output_csv = f"/home/tangyuxin/cleanFastlanes/FastLanes/data/time_series/tables/"+dataset+"/"+filename+f"_{x}.csv"
    truncate_csv(input_csv, output_csv, x)

    