
extern "C"{
	#include "../zhelpers.h"
}
#include <pthread.h>

static const char* A = "A";
static const char* B = "B";
static const char* END = "END";
static const char* msg = "this is a message";

struct thread_stus{
	int val;
};

static void* worker_a(void* args){
	char* identity = (char*)args;
	void* context = zmq_init(1);
	void* worker = zmq_socket(context, ZMQ_DEALER);
	zmq_setsockopt(worker, ZMQ_IDENTITY, identity, 1);
	zmq_connect(worker, "ipc://routing.ipc");

	while(1){
		zmq_msg_t msg;
		zmq_msg_init(&msg);
		int rc = zmq_msg_recv(&msg, worker, ZMQ_DONTWAIT);
		char* request = (char*)zmq_msg_data(&msg);
		int len = zmq_msg_size(&msg);
		char buff[1024];
		memcpy(buff, request, len);
		buff[len] = '\0';
		bool isFinish = strcmp(buff, END) == 0;
		if(isFinish)
			break;
		else if(len > 0)
			printf("%s recv msg %s\r\n",identity, buff);
	}

	zmq_msg_t finMsg;
	zmq_msg_init_size(&finMsg, strlen(identity));
	memcpy(zmq_msg_data(&finMsg), identity, strlen(identity));
	zmq_msg_send(&finMsg, worker, 0);

	struct thread_stus* stusp = (struct thread_stus*) malloc(sizeof(struct thread_stus));
	stusp->val = 101;
	pthread_exit((void*)stusp);
}

int main(int argc, char** argv){
	void* context = zmq_init(1);
	void* client = zmq_socket(context, ZMQ_ROUTER);
	zmq_bind(client, "ipc://routing.ipc");

	pthread_t pids[2];
	pthread_create(&pids[0], NULL, worker_a, (void*)A);
	pthread_create(&pids[1], NULL, worker_a, (void*)B);

	sleep(1);

	srandom((unsigned) time(NULL));
	for(int i=0; i<=20; i++){
		const char* dest = random()%2==0 ? A : B;
		zmq_msg_t destMsg;
		zmq_msg_init_size(&destMsg, strlen(dest));
		memcpy(zmq_msg_data(&destMsg), dest, strlen(dest));
		zmq_msg_send(&destMsg, client, ZMQ_SNDMORE);

		zmq_msg_t zmqMsg;
		zmq_msg_init_size(&zmqMsg, strlen(msg));
		memcpy(zmq_msg_data(&zmqMsg), msg, strlen(msg));
		zmq_msg_send(&zmqMsg, client, 0);
	}
	zmq_msg_t destA;
	zmq_msg_init_size(&destA, strlen(A));
	memcpy(zmq_msg_data(&destA), A, strlen(A));
	zmq_msg_send(&destA, client, ZMQ_SNDMORE);

	zmq_msg_t msgA;
	zmq_msg_init_size(&msgA, strlen(END));
	memcpy(zmq_msg_data(&msgA), END, strlen(END));
	zmq_msg_send(&msgA, client, 0);

	zmq_msg_t destB;
	zmq_msg_init_size(&destB, strlen(B));
	memcpy(zmq_msg_data(&destB), B, strlen(B));
	zmq_msg_send(&destB, client, ZMQ_SNDMORE);

	zmq_msg_t msgB;
	zmq_msg_init_size(&msgB, strlen(END));
	memcpy(zmq_msg_data(&msgB), END, strlen(END));
	zmq_msg_send(&msgB, client, 0);

	int recvCnt = 0;
	while(true){
		zmq_msg_t dealerMsg;
		zmq_msg_init(&dealerMsg);
		int rc = zmq_msg_recv(&dealerMsg, client, ZMQ_DONTWAIT); //recv two msg, the first is the src of the msg , and second is msg
		if(rc > 0){
			int len = zmq_msg_size(&dealerMsg);
			recvCnt++;
			char buff[1024];
			memcpy(buff, zmq_msg_data(&dealerMsg), len);
			buff[len] = '\0';
			printf("router recv msg from dealer %s\n", buff);
		}
		if(recvCnt == 4)
			break;
	}

	zmq_close(client);
	zmq_term(context);

	void* stup=NULL;
	pthread_join(pids[0], &stup);
	pthread_join(pids[1], &stup);

	printf("%d\n", ((struct thread_stus*)stup)->val);
	free(stup);
	stup = NULL;

	return 0;
}
