SRCS	= $(shell /bin/ls *.cpp)
SRCS1	= $(shell /bin/ls char-stack?.cpp)
OBJS	= $(SRCS:.cpp=.o)
OBJS1	= $(SRCS1:.cpp=.o)
PROGS	= char-stack-test
CPP     = g++-13



%.o:	%.cpp
	$(CPP) -c $<
	
$(PROGS): $(OBJS)
	$(CPP) -o $@ $(OBJS)

$(SRCS):	char-stack.h 
$(SRCS1):	char-stack.h 

lib:	$(OBJS1)
	ar rsuv libintstack.a $(OBJS1)


clean:
	/bin/rm -f $(PROGS) $(OBJS) *.a *~
