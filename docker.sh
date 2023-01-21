
cd docker && \
docker build --tag oadbg-docker . && \
docker cp $(docker create oadbg-docker:latest):/build/test .

#docker rm $(docker ps -a -f ancestor=oadbg-docker -q)
#docker image rm oadbg-docker
