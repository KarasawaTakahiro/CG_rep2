
#define MARBLE_SIZE 0.25
#define MARBLE_MAX_NUM 10

#define BLOCK_SHOW 1
#define BLOCK_HIDE 0

/*
    モデルの種類を示す定数
*/
#define MODEL_TYPE_POST 100
#define MODEL_TYPE_STRAIGHT 101


/*
    各モデルの数値を表す定数
    メタセコイア上の実測値
*/

// 柱パーツ
#define POST_PATH "post_2.mqo"
#define POST_HEIGHT 50.0           // 最大の高さ
#define POST_WIDTH 34.0            // 最大の幅
#define POST_INTERNAL_RADIUS 10.0  // 最内側の半径
#define POST_OUTER_RADIUS 17.0     // 最外側の半径

// 直線パーツ
#define STRAIGHT_PATH "straight_2.mqo"
#define STRAIGHT_HEIGHT 50.0
#define STRAIGHT_WIDTH 194.6
#define STRAIGHT_DEPTH 34.0
#define STRAIGHT_INTERNAL_RADIUS 10.0                // 最内側の半径
#define STRAIGHT_OUTER_RADIUS 17.0                   // 最外側の半径
#define STRAIGHT_BRIGDE_BASE_HIGHEST 2.3             // 通路の底面で一番高い点
#define STRAIGHT_BRIDGE_BASE_LOWEST 1.8              // 通路の底面で一番低い点
#define STRAIGHT_BRIDGE_WIDTH 20.0                   // 通路の幅
#define STRAIGHT_BRIDGE_DEPTH 7.7                    // 通路の深さ
#define STRAIGHT_BRIDGE_OVERALL_LENGTH 114.7         // 通路の全長
#define STRAIGHT_BRIDGE_ENTRANCE_SIDE_LENGTH 89.5    // 中心から入り口側の端までの長さ
#define STRAIGHT_BRIDGE_OUTLET_SIDE_LENGTH 25.2      // 中心から出口側の端までの長さ
#define STRAIGHT_BRIDGE_LOOKABLE_LENGTH 125.0        // ビー玉が見える範囲の長さ
