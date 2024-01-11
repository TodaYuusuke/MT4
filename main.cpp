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
	Quaternion rotation0 = Quaternion::CreateRotateAxisAngleQuaternion(Vector3{ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = Quaternion::CreateRotateAxisAngleQuaternion(Vector3{ 0.71f, 0.0f, 0.71f }, 3.141592f);

	Quaternion interpolater0 = Quaternion::Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolater1 = Quaternion::Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolater2 = Quaternion::Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolater3 = Quaternion::Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolater4 = Quaternion::Slerp(rotation0, rotation1, 1.0f);


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
		interpolater0.DrawDisplay("interpolater0, Slerp(q0, q1, 0.0f)", 0, 0);
		interpolater1.DrawDisplay("interpolater1, Slerp(q0, q1, 0.3f)", 0, 20);
		interpolater2.DrawDisplay("interpolater2, Slerp(q0, q1, 0.5f)", 0, 40);
		interpolater3.DrawDisplay("interpolater3, Slerp(q0, q1, 0.7f)", 0, 60);
		interpolater4.DrawDisplay("interpolater4, Slerp(q0, q1, 1.0f)", 0, 80);


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
