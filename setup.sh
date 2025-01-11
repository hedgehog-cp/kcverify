# TODO: もっと安全な方法にする.
# curl https://raw.githubusercontent.com/Tibowl/api_start2/refs/heads/master/parsed/api_mst_ship.json     > ./assets/api_mst_ship/api_mst_ship.json
# curl https://raw.githubusercontent.com/Tibowl/api_start2/refs/heads/master/parsed/api_mst_slotitem.json > ./assets/api_mst_slotitem/api_mst_slotitem.json
# curl https://raw.githubusercontent.com/ElectronicObserverEN/Data/refs/heads/master/Data/FitBonuses.json > ./assets/fit_bonus/fit_bonus.json

jq -r '.[] | "{\(.api_id), \"\(.api_name)\", \(.api_stype)},"'   ./assets/api_mst_ship/api_mst_ship.json         > ./include/constants/ship.hpp.inc      && touch ./include/constants/ship.hpp
jq -r '.[] | "{\(.api_id), \"\(.api_name)\", \(.api_type[3])},"' ./assets/api_mst_slotitem/api_mst_slotitem.json > ./include/constants/equipment.hpp.inc && touch ./include/constants/equipment.hpp