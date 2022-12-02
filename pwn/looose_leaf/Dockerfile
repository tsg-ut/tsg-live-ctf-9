FROM ubuntu:22.04


RUN apt-get update && \
        apt-get -y upgrade && \
        apt-get install -y \
            xinetd \
            iproute2

RUN groupadd -r user && useradd -r -g user user

COPY --chown=root:user ./build/start.sh /home/user/start.sh
COPY --chown=root:root ./build/ctf.conf /etc/xinetd.d/ctf
COPY --chown=root:user ./build/flag.txt /home/user/flag.txt
COPY --chown=root:user ./dist/chall /home/user/chall
COPY --chown=root:user ./dist/libc.so.6 /home/user/libc.so.6

WORKDIR /home/user

RUN chmod 444 ./flag.txt && \
    chmod 555 ./chall && \
    chmod 555 ./libc.so.6 &&\
    chmod 555 ./start.sh && \
    chmod 444 /etc/xinetd.d/ctf

USER user
EXPOSE 8888

CMD ["xinetd","-dontfork","-f","/etc/xinetd.d/ctf"]

