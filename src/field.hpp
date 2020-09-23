int H, W;

int dh[4] = {0, 0, -1, 1};
int dw[4] = {-1, 1, 0, 0};

bool is_in_field(int i, int j){
    return i >= 0 && i < H && j >= 0 && j < W;
}