#include <Novice.h>
#include <math/Math.h>

const char kWindowTitle[] = "LE2B_14_トダユウスケ";

using namespace LWP::Math;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ** 変数宣言 ** //
	Vector3 from0 = Vector3{ 1.0f,0.7f,0.5f }.Normalize();
	Vector3 to0 = -1.0f * from0;
	Vector3 from1 = Vector3{ -0.6f,0.9f,0.2f }.Normalize();
	Vector3 to1 = Vector3{ 0.4f,0.7f,-0.5f }.Normalize();
	Matrix4x4 rotateMatrix0 = Matrix4x4::DirectionToDirection(Vector3{ 1.0f,0.0f,0.0f }.Normalize(), Vector3{ -1.0f,0.0f,0.0f }.Normalize());
	Matrix4x4 rotateMatrix1 = Matrix4x4::DirectionToDirection(from0, to0);
	Matrix4x4 rotateMatrix2 = Matrix4x4::DirectionToDirection(from1, to1);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 描画
		rotateMatrix0.DrawDisplay("rotateMatrix0" ,0 ,0);
		rotateMatrix1.DrawDisplay("rotateMatrix1", 0, 100);
		rotateMatrix2.DrawDisplay("rotateMatrix2", 0, 200);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
