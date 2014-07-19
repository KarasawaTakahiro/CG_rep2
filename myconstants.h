
/*
    ビー玉に関する定義
 */
#define MARBLE_SIZE 0.25
#define MARBLE_MAX_NUM 10
#define MARBLE_NOT_HIT -1

/*
    ブロックに関する定義
 */
#define BLOCK_SHOW 1
#define BLOCK_HIDE 0

/*
    衝突判定に関する定義
 */
#define IS_HIT 1
#define NOT_HIT 0

/*
   モデルの種類を示す定数
 */
#define MODEL_TYPE_POST 100
#define MODEL_TYPE_STRAIGHT 101

#define MODEL_MAX_DEVISION 3  // モデルの最大分割数

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
#define STRAIGHT_PATH "straight.mqo"
#define STRAIGHT_HEIGHT 28.3  // 最高点
#define STRAIGHT_WIDTH 160.5
#define STRAIGHT_DEPTH 20.0
#define STRAIGHT_RADIUS 10.0                   // 通路の半径
#define STRAIGHT_GROOVE_DEPTH 7.7             // 通路の深さ
#define STRAIGHT_BASE_HIGHEST 18.6             // 通路の底面で一番高い点
#define STRAIGHT_BASE_LOWEST 1.3              // 通路の底面で一番低い点
#define STRAIGHT_OVERALL_LENGTH 160.5         // 通路の底辺の幅(z軸から見た底面の長さ)
#define STRAIGHT_LENGTH_UPPER_SIDE 91.5       // 通路の底辺の幅(中心から上がっている方の端まで)
#define STRAIGHT_LENGTH_LOWER_SIDE 69.0       // 通路の底辺の幅(中心から下がっている方の端まで)

// 橋パーツの入り口側
#define BRIDGE_ENTRANCE_PATH "bridge_entrance.mqo"
#define BRIDGE_ENTRANCE_CORRECTION_X 80.0  // 柱パーツの中心とこのパーツの中心をそろえる時のX軸方向の補正
#define BRIDGE_ENTRANCE_HIGHT 50.0                          // 最大値
#define BRIDGE_ENTRANCE_WIDTH 34.0                          // 最大値
#define BRIDGE_ENTRANCE_DEPTH 34.0                          // 最大値
#define BRIDGE_ENTRANCE_INTERNAL_RADIUS 10.0                // 最内側の半径
#define BRIDGE_ENTRANCE_OUTER_RADIUS 17.0                   // 最外側の半径
#define BRIDGE_ENTRANCE_LOOKABLE_LENGTH_FROM_ORIGIN 63.0    // 中心から入り口側の端までの長さ

// 橋パーツの出口側
#define BRIDGE_OUTLET_PATH "bridge_outlet.mqo"
#define BRIDGE_OUTLET_CORRECTION_X -80.0                  // 補正値
#define BRIDGE_OUTLET_HIGHT 50.0                            // 最大値
#define BRIDGE_OUTLET_WIDTH 34.0                            // 最大値
#define BRIDGE_OUTLET_DEPTH 34.0                            // 最大値
#define BRIDGE_OUTLET_INTERNAL_RADIUS 10.0                  // 最内側の半径
#define BRIDGE_OUTLET_OUTER_RADIUS 17.0                     // 最外側の半径
#define BRIDGE_OUTLET_LOOKABLE_LENGTH_FROM_ORIGIN 63.0      // 中心から出口側の端までの長さ

