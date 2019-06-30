#include <cstdint>
#include <vector>
#include <iostream>

enum class PageRepAlgo{
    FWF,
    FIFO,
    OPT
};

void printList (std::vector<int> List){
    std::cout<<"[";
    for (elem : List) {
        std::cout<<elem<<", ";
    }
    std::cout<<"]"<<std::endl;
}

std::vector<int> clearList (int frameBufferSize){
    std::vector<int> temp;
    for (int i=0; i<frameBufferSize; i++){
        temp.push_back(-1);
    }
    return temp;
}

bool inBuffer (int x, std::vector<int> buffer){
    int counter=0;
    for (elem : buffer){
        if (x==elem){
            counter++;
        }
    }
    if (counter>0){
        return true;
    } else {
        return false;
    }
}

std::vector<int> placeElem (int elem, int pointer, std::vector<int> buffer) {
    buffer[pointer]=elem;
    return buffer;
}

bool ifFull (std::vector<int> List){
    int counter=0;
    for (elem : List){
        if (elem==-1){
            counter++;
        }
    }
    if (counter>0) {
        return false;
    } else {
        return true;
    }
}

int soFar (std::vector<int> page, std::vector<int> buffer, int pointer){
    int maxCounter = 0;
    int index=0;
    for (elem : buffer){
        int counter=0;
        for (pageElem : page) {
            if (elem==pageElem){
                break;
            }
            counter++;
        }
        if (counter>maxCounter){
            maxCounter=counter;
            pointer=index;
        }
        index++;
    }
    return pointer;
}

std::vector<int> page(PageRepAlgo algo, int frameBufferSize, std::vector<int> pageReference){
    // implementation here
    std::vector<int> output;
    std::vector<int> frameBuffer;
    int pointer=0;
    if ((int) algo==0){
        std::cout<<"FWF"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        for (elem : pageReference){
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (pointer>=frameBufferSize){
                    pointer=0;
                    frameBuffer=clearList(frameBufferSize);
                }
                frameBuffer=placeElem(elem, pointer, frameBuffer);
                pointer++;
            }
        }
    }
    else if ((int) algo==1){
        std::cout<<"FIFO"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        for (elem : pageReference){
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (pointer>=frameBufferSize){
                    pointer=0;
                }
                frameBuffer=placeElem(elem, pointer, frameBuffer);
                pointer++;
            }
        }
    }else if ((int) algo==2) {
        std::cout<<"OPT"<<std::endl;
        printList(pageReference);
        frameBuffer=clearList(frameBufferSize);
        std::vector<int> tempPage=pageReference;
        for (elem : pageReference){
            if (inBuffer(elem, frameBuffer)){
                output.push_back(0);
            } else {
                output.push_back(1);
                if (ifFull(frameBuffer)){
                    pointer=soFar(tempPage,frameBuffer,pointer);
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                } else {
                    frameBuffer=placeElem(elem, pointer, frameBuffer);
                    pointer++;
                }
            }
            tempPage.erase(tempPage.begin());
        }
    }
    return output;
}

int main() {
    std::vector<int> pageReference = {7,0,1,2,0,3,4,2,1,0,1};
    int frameBufferSize = 5;

    std::vector<int> FWFoutput = page(PageRepAlgo::FWF, frameBufferSize, pageReference);
    printList(FWFoutput);
    std::vector<int> FIFOoutput = page(PageRepAlgo::FIFO, frameBufferSize, pageReference);
    printList(FIFOoutput);
    std::vector<int> OPToutput = page(PageRepAlgo::OPT, frameBufferSize, pageReference);
    printList(OPToutput);
}

