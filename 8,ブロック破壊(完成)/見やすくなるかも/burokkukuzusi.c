// ブロック崩しゲーム
// コンソールにテキストで描画し、ボールとパドルを動かしてブロックを壊す簡易ゲーム

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

// ====== 定数定義 ======
#define FIELD_WIDTH   (14)                 // フィールドの横幅
#define FIELD_HEIGHT  (FIELD_WIDTH * 2)    // フィールドの高さ（縦長にしている）
#define FPS           (25)                 // フレームレート（1秒間に25更新）
#define INTERVAL      (1000 / FPS)         // 1フレームあたりの時間(ms)
#define PADDLE_WIDTH  (7)                  // パドルの横幅

// ====== グローバル変数（ボール関連） ======
int ballX;                // ボールのX座標
int ballY;                // ボールのY座標
int ballVelocityX = 1;    // ボールの速度（X方向）
int ballVelocityY = 1;    // ボールの速度（Y方向）

// ====== グローバル変数（パドル関連） ======
int paddleX;              // パドルの左端X座標
int paddleY;              // パドルのY座標

// ====== フィールド情報 ======
int field[FIELD_HEIGHT][FIELD_WIDTH];  // ブロックの有無を管理する2D配列（1=ブロックあり）

// ---------------------------------------------------------------
// 画面描画関数
// ---------------------------------------------------------------
void DrawScreen() {
    system("cls");  // 画面クリア（Windows 専用）

    // 上部の枠描画
    for (int x = 0; x < FIELD_WIDTH + 2; x++)
        printf("■");
    printf("\n");

    // メインフィールド描画
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        printf("■");  // 左枠

        for (int x = 0; x < FIELD_WIDTH; x++) {

            // ボールの描画
            if ((x == ballX) && (y == ballY))
                printf("●");

            // パドル描画
            else if ((y == paddleY) && (x >= paddleX) && (x < paddleX + PADDLE_WIDTH))
                printf("■");

            // ブロック描画
            else if (field[y][x])
                printf("□");

            // 何もない場所
            else
                printf(" ");
        }

        printf("■");  // 右枠
        printf("\n");
    }

    // 下部の枠描画
    for (int x = 0; x < FIELD_WIDTH + 2; x++)
        printf("■");
}

// ---------------------------------------------------------------
// 初期化：ボール・パドル・ブロック配置のリセット
// ---------------------------------------------------------------
void Reset() {
    // ボールの初期位置
    ballX = rand() % FIELD_WIDTH;
    ballY = FIELD_HEIGHT / 3;

    // ボールの向きランダム（左右）
    ballVelocityX = (rand() % 2) ? 1 : -1;
    ballVelocityY = 1;

    // パドルの初期配置（画面下）
    paddleX = (FIELD_WIDTH - PADDLE_WIDTH) / 2;
    paddleY = FIELD_HEIGHT - 3;

    // ブロック配置（フィールド上部 25% に敷き詰める）
    for (int y = 0; y < FIELD_HEIGHT / 4; y++)
        for (int x = 0; x < FIELD_WIDTH; x++)
            field[y][x] = 1;

    DrawScreen();
}

// ---------------------------------------------------------------
// メイン関数
// ---------------------------------------------------------------
int main() {
    srand((unsigned int)time(NULL));  // 乱数の初期化

    Reset();  // 初期配置

    clock_t lastClock = clock();

    // =============================
    // メインゲームループ
    // =============================
    while (1) {
        clock_t nowClock = clock();

        // フレーム間隔を満たしたら更新処理を実行
        if (nowClock >= lastClock + INTERVAL) {

            // ---- ボールの移動 ----
            ballX += ballVelocityX;
            ballY += ballVelocityY;

            // ---- 壁との衝突判定（左右）----
            if (ballX <= 0)
                ballVelocityX = 1;

            if (ballX >= FIELD_WIDTH - 1)
                ballVelocityX = -1;

            // ---- 壁（上）との衝突 ----
            if (ballY <= 0)
                ballVelocityY = 1;

            // ---- 下に落ちた場合（ミス） ----
            if (ballY >= FIELD_HEIGHT - 1)
                ballVelocityY = -1;

            // ---- パドルとの衝突 ----
            if ((ballY == paddleY - 1) &&
                (ballX >= paddleX - 1) &&
                (ballX < paddleX + PADDLE_WIDTH + 1)) {

                // パドルの左半分 → 左向き反射
                if (ballX < paddleX + PADDLE_WIDTH / 2)
                    ballVelocityX = -1;
                else
                    ballVelocityX = 1;

                ballVelocityY = -1;
            }

            // ---- ブロックとの衝突判定 ----
            for (int x = ballX - 1; x <= ballX + 1; x++) {
                int y = ballY - 1;  // ボール上部を中心に判定

                if ((y < 0) || (x < 0) || (x >= FIELD_WIDTH))
                    continue;

                // ブロックがある場合
                if (field[y][x]) {
                    field[y][x] = 0;      // ブロック破壊
                    ballVelocityY = 1;    // 反射
                }
            }

            DrawScreen();       // 画面更新
            lastClock = nowClock;

            // ---- ミスした場合：ゲームリセット ----
            if (ballY >= FIELD_HEIGHT - 1)
                Reset();
        }

        // =============================
        // キーボード入力（非ブロッキング）
        // =============================
        if (_kbhit()) {
            switch (_getch()) {
            case 'a': paddleX--; break;   // 左移動
            case 'd': paddleX++; break;   // 右移動
            }

            // パドルが画面外に出ないように制限
            if (paddleX < 0)
                paddleX = 0;

            if (paddleX > FIELD_WIDTH - PADDLE_WIDTH)
                paddleX = FIELD_WIDTH - PADDLE_WIDTH;

            DrawScreen();  // 入力後も画面更新
        }
    }

    getch();
}