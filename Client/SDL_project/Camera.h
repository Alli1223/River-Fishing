#pragma once
class Camera
{
public:
	//! Constructor
	Camera();
	//! Destructor
	~Camera();

	//! Camera Mode
	enum {
		TARGET_MODE_NORMAL = 0,
		TARGET_MODE_CENTER
	};
	//! On move
	void OnMove(int MoveX, int MoveY);

	int TargetMode;

	//! Get positions
	int getX();
	int getY();
	//! Set positions
	int setX(int newX) { return X = newX; }
	int setY(int newY) { return Y = newY; }
	void SetPos(int X, int Y);

	//! Get and set speeds
	float getCameraSpeed() { return cameraSpeed; }
	float setCameraSpeed(float newSpeed) { return cameraSpeed = newSpeed; }
	
	//! Set target
	void SetTarget(int* X, int* Y);

	int WindowWidth = 0;
	int WindowHeight = 0;
	glm::vec2 ChunksOnScreen;

	//! Lerp to target
	void Camera::Lerp_To(glm::vec2 target, float increment);

	glm::vec2 getPosition() { return { X, Y }; }

	static Camera CameraControl;

private:
	int X;
	int Y;

	

	float cameraSpeed = 0.25;

	int* TargetX;
	int* TargetY;

	




};


