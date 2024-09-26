FROM ubuntu:latest

RUN apt-get -y update && apt-get install -y

RUN apt-get install -y clang
RUN apt-get install -y cmake
RUN apt-get install -y mpi-default-dev

COPY . /usr/src/cpp_test

WORKDIR /usr/src/cpp_test

RUN cmake -S . -B build
RUN cmake --build build

CMD ["./build/test"]