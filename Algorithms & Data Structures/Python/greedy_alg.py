states_needed = {"mt", "wa", "or", "id", "nv", "ut", "са", "az"}
stations = {"kone": {"id", "nv", "ut"}, "ktwo": {"wa", "id", "mt"}, "kthree": {"or", "nv", "са"},
            "kfour": {"nv", "ut"}, "kfive": {"ca", "az"}}
final_stations = set()

while states_needed:
    best_station = None
    states_covered = set()
    for station, states_for_station in stations.items():
        covered = states_needed & states_for_station
        if len(covered) > len(states_covered):
            best_station = station
            states_covered = covered

    states_needed -= states_covered
    final_stations.add(best_station)

print(final_stations)
