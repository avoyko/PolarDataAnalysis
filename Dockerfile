FROM ubuntu:latest

#installing python and must-have python packages
RUN apt-get update -y --fix-missing\
    && apt install python3 -y \
    && apt install python3-pip -y \
    && pip3 install numpy \
    && pip3 install tensorflow \
    && pip3 install scikit-learn \
    && pip3 install keras_tuner \
    && pip3 install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib


