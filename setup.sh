#!/bin/bash

# TODO: もっと安全な方法にする.
curl https://raw.githubusercontent.com/Tibowl/api_start2/refs/heads/master/parsed/api_mst_ship.json             > ./assets/api_mst_ship.json
curl https://raw.githubusercontent.com/Tibowl/api_start2/refs/heads/master/parsed/api_mst_slotitem.json         > ./assets/api_mst_slotitem.json
curl https://raw.githubusercontent.com/ElectronicObserverEN/Data/refs/heads/master/Data/FitBonuses.json         > ./assets/fit_bonuses.json
curl https://raw.githubusercontent.com/KC3Kai/kancolle-replay/refs/heads/master/js/data/mst_slotitem_bonus.json > ./assets/mst_slotitem_bonus.json
