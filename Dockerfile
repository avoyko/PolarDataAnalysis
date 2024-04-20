FROM ubuntu:latest

#installing python and must-have python packages
#RUN apt-get update -y --fix-missing\
#    && apt install python3 -y \
#    && apt install python3-pip -y \
#    && pip3 install numpy \
#    && pip3 install tensorflow \
#    && pip3 install scikit-learn \
#    && pip3 install keras_tuner \
#    && pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib



#installing mysql
RUN apt-get update && apt-get -y install mysql-server \
    && apt-get install -y wget \
    && wget 'http://archive.ubuntu.com/ubuntu/pool/main/o/openssl/libssl1.1_1.1.1f-1ubuntu2_amd64.deb' \
    && dpkg -i libssl1.1_1.1.1f-1ubuntu2_amd64.deb \
    && apt-get install -y libsasl2-2 \
    && apt-get install -y libmbedtls-dev \
    && wget 'https://dev.mysql.com/get/Downloads/MySQL-8.0/mysql-community-client-plugins_8.0.25-1ubuntu20.04_amd64.deb' \
    && wget 'https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn9_8.0.25-1ubuntu20.04_amd64.deb' \
    && wget 'https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn8-2_8.0.25-1ubuntu20.04_amd64.deb' \
    && wget 'https://dev.mysql.com/get/Downloads/Connector-C++/libmysqlcppconn-dev_8.0.25-1ubuntu20.04_amd64.deb' \
    && dpkg -i mysql-community-client-plugins_8.0.25-1ubuntu20.04_amd64.deb \
    && dpkg -i libmysqlcppconn9_8.0.25-1ubuntu20.04_amd64.deb \
    && dpkg -i libmysqlcppconn8-2_8.0.25-1ubuntu20.04_amd64.deb \
    && dpkg -i libmysqlcppconn-dev_8.0.25-1ubuntu20.04_amd64.deb \
    && apt-get install -y libmysqlcppconn-dev



RUN wget "https://dev.mysql.com/get/Downloads/Connector-C++/mysql-connector-c++-8.3.0-linux-glibc2.28-x86-64bit.tar.gz" \
    && tar -zxvf mysql-connector-c++-8.3.0-linux-glibc2.28-x86-64bit.tar.gz -C . \
    && mv mysql-connector-c++-8.3.0-linux-glibc2.28-x86-64bit mysql-connector-c++

RUN apt-get update \
    && apt-get install -y vim \
    && apt-get install -y git \
    && apt-get install -y cmake \
    && apt-get install -y g++ \
    && apt-get install -y libboost-all-dev \
    && apt-get install -y libasio-dev

RUN mkdir "repos" && cd repos \
    && git clone "https://github.com/CrowCpp/Crow" \
    && cd Crow && mkdir build && cd build \
    && cmake .. \
    && make install \
    && apt-get install htop


RUN git clone 'https://github.com/avoyko/PolarDataAnalysis' \
    && cd PolarDataAnalysis && cd src \
    && cmake .. \
    && cmake -Dmysql-concpp_DIR=/mysql-connector-c++ ..

