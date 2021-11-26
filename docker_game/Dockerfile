From ubuntu
WORKDIR /root/
RUN apt-get update && apt-get install -y redis-tools
COPY game /root/
COPY game_start.sh /root/
COPY random_first.txt /root/
COPY random_last.txt /root/
EXPOSE 8899
# ENTRYPOINT ["./game"]
ENTRYPOINT ["./game_start.sh"]
