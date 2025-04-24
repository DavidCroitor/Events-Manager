#pragma once
#include "Event.h"
#include <vector>

void merge(std::vector<Event> &events, int left, int mid, int right);
void mergeSort(std::vector<Event> &events, int left, int right);