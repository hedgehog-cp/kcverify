#!/usr/bin/sh

# *.incファイルを生成する

# {装備ID, 装備名, 装備種3, 装備種4, 火力, 雷装, 爆装}
awk 'NR != 1 {
    gsub("\"", ""); printf("%d,%s,%d,%d,%d,%d,%d\n", $1, $3, $6, $7, $9, $10, $18)
}' FS=',' ./asset/装備図鑑_データ用.csv \
| sort -k 2,2 -t ',' \
| awk '{
    printf("{%d, \"%s\", %d, %d, %d, %d, %d}, \n", $1, $2, $3, $4, $5, $6, $7)
}' FS=',' > ./include/master/equipment.inc

# {艦船ID, 艦名, 読み, 艦種, 艦型, 未改造ID}
awk -F, '
# 未改造IDを求める. original_idsに格納.
NR == FNR {
    if (FNR > 1) {
        id = $1
        yomi = $4
        sort_id = $7
        if (sort_id % 10 == 1 && !(yomi in original_ids)) {
            original_ids[yomi] = id
        }
    }
    next
}
# 必要なマスタデータを書き出す.
NR != 1 && FNR > 1 {
    yomi = $4
    original_id = (yomi in original_ids) ? original_ids[yomi] : 0
    printf("{%d, %s, %s, %d, %d, %d}, \n", $1, $3, $4, $5, $6, original_id)
}' ./asset/艦船図鑑_データ用.csv ./asset/艦船図鑑_データ用.csv > ./include/master/ship.inc
