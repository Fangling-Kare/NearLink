# 基础镜像
FROM ubuntu:20.04

# 设置环境变量
ENV DEBIAN_FRONTEND=noninteractive

# 更新系统并安装必要的工具和依赖
RUN apt-get update && apt-get install -y \
    sudo \
    software-properties-common \
    wget \
    curl \
    build-essential \
    cmake \
    python3 \
    python3-pip \
    python3-setuptools \
    && rm -rf /var/lib/apt/lists/*

# 设置 Python3 为默认 Python
RUN ln -s /usr/bin/python3 /usr/bin/python

# 安装 kconfiglib 和 pycparser
COPY requirements.txt /tmp/
RUN pip3 install -r /tmp/requirements.txt

# 配置 bash 作为默认 Shell
RUN echo "dash dash/sh boolean false" | debconf-set-selections && \
    dpkg-reconfigure -p low dash

# 设置工作目录
WORKDIR /workspace

# 将用户的源码和其他文件（例如README）添加到容器
COPY . /workspace

# 执行完毕后的默认命令
CMD ["/bin/bash"]
