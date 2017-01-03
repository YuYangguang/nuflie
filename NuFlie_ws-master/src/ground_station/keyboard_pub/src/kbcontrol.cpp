#include "kbcontrol.h"
#include "std_msgs/Int32.h"

struct termios cooked, raw;
int kfd = 0;
bool kbstate = false;

int main(int argc, char** argv)
{
	ros::init(argc,argv,"tbk", ros::init_options::AnonymousName | ros::init_options::NoSigintHandler);
    kbcontrol_node tbk;
    boost::thread t = boost::thread(boost::bind(&kbcontrol_node::keyboardLoop, &tbk));
	ros::spin();	
	t.interrupt();
	t.join();

	tcsetattr(kfd, TCSANOW, &cooked);
	
	return(0);
}

void kbcontrol_node::keyboardLoop()
{
    std_msgs::Int32 c;
   // int kfd = 0;
	bool dirty = false;
   // struct termios cooked, raw;
	
	// get the console in raw mode
	tcgetattr(kfd, &cooked); //tcgetattr是一个函数，成功返回零；失败返回非零，发生失败接口将设置errno错误标识
	memcpy(&raw, &cooked, sizeof(struct termios));
	raw.c_lflag &=~ (ICANON | ECHO);
	raw.c_cc[VEOL] = 1;
	raw.c_cc[VEOF] = 2;
	tcsetattr(kfd, TCSANOW, &raw);
	
// 	puts("Reading from keyboard");
// 	puts("Use WASD keys to control the robot");
// 	puts("Press Shift to move faster");
	puts("Reading from keyboard");
	puts("Use:");
	puts("i,k,j,l,u,o: for forward, backward, left, right,turn left, turn right value = 0.1");
	puts("q,a: for up, down, value = 1");
	puts("blank space: for stop and hover. ");
	puts("h: for hover");
	puts("s,d: for takeoff and land");
	
	struct pollfd ufd;
	ufd.fd = kfd;
	ufd.events = POLLIN;




	for(;;)
	{
		boost::this_thread::interruption_point();
        //c.data='z';
		
		// get the next event from the keyboard
		int num;
		
		if ((num = poll(&ufd, 1, 250)) < 0)
		{
			perror("poll():");
			return;
		}
		else if(num > 0)
		{
			if(read(kfd, &c, 1) < 0)
			{
				perror("read():");
				return;
			}
		}
		else
		{
			if (dirty == true)
			{
                //stopRobot();
				dirty = false;
			}
			
			continue;
		}


        Publish(c);




	}




}

