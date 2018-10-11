extern "C"{
	#include "../src/3rd/libevent/include/event.h"
	#include "../src/3rd/zmq/include/zmq.h"
	#include <string.h>
	#include <unistd.h>
}

static char dest[16];
static char buff[1024];
struct eventData{
	void* socket;
	void* event;
};

void activeEvent(struct event* ev){
	event_add(ev, NULL);
	event_active(ev, EV_READ, 0);
}

static void mq_read_event(int fd, short what, void *userdata) {
	struct eventData* evData = (struct eventData*) userdata;
	activeEvent((struct event*) evData->event);
	
	uint events = 0;
	size_t eventSize = sizeof(events);
	zmq_getsockopt(evData->socket, ZMQ_EVENTS, &events, &eventSize);
	if( !(events & ZMQ_POLLIN) )
		return;

	void* socket = evData->socket;
	
	zmq_msg_t destMsg;
	zmq_msg_init(&destMsg);
	int rc = zmq_msg_recv(&destMsg, socket, ZMQ_DONTWAIT);
	if(rc == -1)
		return;
	char destBuff[16];
	int len = zmq_msg_size(&destMsg);
	memcpy(destBuff, zmq_msg_data(&destMsg), len);
	destBuff[len] = '\0';
	printf("dest %s %d\n", destBuff, len);

	zmq_msg_t msgMsg;
	zmq_msg_init(&msgMsg);
	rc = zmq_msg_recv(&msgMsg, socket, ZMQ_DONTWAIT);
	if(rc == -1)
		return;
	char msgBuff[1024];
	len = zmq_msg_size(&msgMsg);
	memcpy(msgBuff, zmq_msg_data(&msgMsg), len);
	msgBuff[len] = '\0';
	printf("msg %s %d\n", msgBuff, len);
}

int main(){

	void* context = zmq_init(1);
	void* router = zmq_socket(context, ZMQ_ROUTER);
	int rc = zmq_bind(router, "tcp://127.0.0.1:8988");
	printf("zmq_bind rc %d\n", rc);
	sleep(1);

	int fd = 0;
	size_t fdSize = sizeof(fd);
	zmq_getsockopt(router, ZMQ_FD, &fd, &fdSize);
	if(fd == 0){
		printf("%s\n", "get fd error");
		return -1;
	}

	struct event_base* base = event_base_new();
	//struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	//bufferevent_setcb(bev, onRead, NULL, NULL, router);
	//bufferevent_enable(bev, EV_READ);

	struct eventData evData;
    struct event* readEvent = event_new(base, fd, EV_READ|EV_PERSIST, mq_read_event, &evData);
	activeEvent(readEvent);
	evData.socket = router;
	evData.event = readEvent;

	event_base_dispatch(base);
	event_base_free(base);

	return 0;
}
