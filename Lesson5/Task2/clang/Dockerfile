FROM ubuntu:latest
COPY Project /usr/src/shapes
WORKDIR /usr/src/shapes
RUN apt-get update && apt-get install -y clang cmake build-essential
CMD cmake -B build && cmake --build build --clean-first --target install && cd install && export LD_LIBRARY_PATH=/usr/src/shapes/install/ && ./LT4_1 









