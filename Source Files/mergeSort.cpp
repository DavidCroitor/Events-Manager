#include "mergeSort.h"
#include "Event.h"
#include <vector>

//void merge(std::vector<Event> &events, int left, int mid, int right){
//    int n1 = mid - left + 1;
//    int n2 = right - mid;
//
//    std::vector<Event> Left(n1), Right(n2);
//
//    for (int i = 0; i < n1; i++) {
//        Left[i] = events[left + i];
//    }
//    for (int i = 0; i < n2; i++) {
//        Right[i] = events[mid + 1 + i];
//    }
//
//    int i = 0, j = 0, k = left;
//    while (i < n1 && j < n2) {
//        if (compareDates(Left[i].getDateAndTime(), Right[j].getDateAndTime()) < 0) {
//            events[k] = Right[j];
//            j++;
//        } else {
//            events[k] = Left[i];
//            i++;
//        }
//        k++;
//    }
//
//    while (i < n1) {
//        events[k] = Left[i];
//        i++;
//        k++;
//    }
//
//    while (j < n2) {
//        events[k] = Right[j];
//        j++;
//        k++;
//    }
//}
//
//void mergeSort(std::vector<Event> &events, int left, int right) {
//    if (left < right) {
//        int mid = left + (right - left) / 2;
//
//        mergeSort(events, left, mid);
//        mergeSort(events, mid + 1, right);
//
//        merge(events, left, mid, right);
//    }
//}