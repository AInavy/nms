#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
using namespace std;

typedef struct Bbox{
    float score;
    float x;
    float y;
    float w;
    float h;
}Bbox;

bool sort_score(Bbox box1, Bbox box2){
    return (box1.score > box2.score);
}

float iou(Bbox box1, Bbox box2){
    int x1 = std::max(box1.x, box2.x);
    int y1 = std::max(box1.y, box2.y);
    int x2 = std::min((box1.x + box1.w), (box2.x + box2.w));
    int y2 = std::min((box1.y + box1.h), (box2.y + box2.h));
    if(x2 > x1 && y2 > y1){
        float over_area = (x2 - x1) * (y2 - y1);
        float iou = over_area / (box1.w * box1.h + box2.w * box2.h - over_area);
        return iou;
    }
    else{
        return 0;
    }

}
//method 1
vector<Bbox> nms(vector<Bbox> &vec_boxs, float threshold){
    std::sort(vec_boxs.begin(), vec_boxs.end(), sort_score);
    std::vector<Bbox> del(vec_boxs.size(), false);
    for(int i = 0; i < vec_boxs.size(); i++){
        for(int j = 0; j < vec_boxs.size(); j++){
            float iou_value = iou(vec_boxs[i], vec_boxs[j]);
            if(iou_value > threshold){
                del[j] = true;
            }
        }
    }
    std::vector<Bbox> res;
    for(const auto i :del){
        if(!del[i]){
            res.push_back(vec_boxs[i]);
        }
    }
    return res;
}

//method 2
vector<Bbox> nms2(vector<Bbox> &vec_boxs, float threshold){
    vector<Bbox> res;
    while(vec_boxs.size() >0 ){
        std::sort(vec_boxs.begin(), vec_boxs.end(), sort_score);
        res.push_back(vec_boxs[0]);
        for(int i = 0; i < vec_boxs.size() - 1; i++){
            float iou_value = iou(vec_boxs[0], vec_boxs[i+1]);
            if(iou_value > threshold){
                vec_boxs.erase(vec_boxs[i+1]);
            }
        }
        vec_boxs.erase(vec_boxs[0]);
    }

    return res;
}


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
