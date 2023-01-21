
cd docker && \
docker build --tag oadbg-docker . && \
docker cp $(docker create oadbg-docker:latest):/build/test .

#docker run -t -i oadbg-docker /bin/bash
#docker rm $(docker ps -a -f ancestor=oadbg-docker -q)
#docker image rm oadbg-docker
