#!/bin/bash

#!/bin/bash
# Generate a dummy CA-signed certificate
# Usage: ./make_cert.sh <domain_name>

DOMAIN=$1
if [ -z "$DOMAIN" ]; then
    echo "Usage: $0 <domain_name>"
    exit 1
fi

# 1. Create a Root CA
openssl genrsa -out rootCA.key 4096
openssl req -x509 -new -nodes -key rootCA.key -sha256 -days 3650 -out rootCA.pem -subj "/C=US/ST=State/L=City/O=DummyCA/CN=Dummy Root CA"

# 2. Create Certificate Private Key and CSR
openssl genrsa -out $DOMAIN.key 2048
openssl req -new -key $DOMAIN.key -out $DOMAIN.csr -subj "/C=US/ST=State/L=City/O=Development/CN=$DOMAIN"

# 3. Create extension file for Subject Alternative Name (SAN)
echo "subjectAltName=DNS:$DOMAIN" > extfile.cnf

# 4. Sign the CSR with the Root CA
openssl x509 -req -in $DOMAIN.csr -CA rootCA.pem -CAkey rootCA.key -CAcreateserial -out $DOMAIN.crt -days 825 -sha256 -extfile extfile.cnf

echo "Certificate generated: $DOMAIN.crt"
echo "Private Key: $DOMAIN.key"






