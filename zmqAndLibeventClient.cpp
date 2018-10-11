#include "../src/3rd/zmq/include/zmq.h"
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv){
	void* context = zmq_init(1);
	void* worker = zmq_socket(context, ZMQ_DEALER);
	zmq_setsockopt(worker, ZMQ_IDENTITY, "A", 1);
	int rc = zmq_connect(worker, "tcp://127.0.0.1:8988");

	//printf("connect rc %d\n", rc);
	zmq_msg_t msg;
	const char* msgStr = "helloxx";
	zmq_msg_init_size(&msg, strlen(msgStr));
	memcpy(zmq_msg_data(&msg), (void*)msgStr, strlen(msgStr));
	zmq_msg_send(&msg, worker, 0);
	sleep(1);
	return 0;
}
