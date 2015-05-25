import requests, time, uuid, hmac, hashlib, base64, json
BASE_URL = 'https://vpn.viridian.io/'
API_TOKEN = 'ND89GyAcm5dsgNjfEQDqjNhpdNeAAROJ'
API_SECRET = 'uJvR8uaeLjSlzMpRzp4mU4CGk4HdpBtC'

def auth_request(method, path, headers=None, data=None):
    auth_timestamp = str(int(time.time()))
    auth_nonce = uuid.uuid4().hex
    auth_string = '&'.join([API_TOKEN, auth_timestamp, auth_nonce,
        method.upper(), path] + ([data] if data else []))
    auth_signature = base64.b64encode(hmac.new(
        API_SECRET, auth_string, hashlib.sha256).digest())
    auth_headers = {
        'Auth-Token': API_TOKEN,
        'Auth-Timestamp': auth_timestamp,
        'Auth-Nonce': auth_nonce,
        'Auth-Signature': auth_signature,
    }
    if headers:
        auth_headers.update(headers)
    return getattr(requests, method.lower())(
        BASE_URL + path,
        verify=False,
        headers=auth_headers,
        data=data,
    )

response = auth_request('GET', '/user/555c0a448fabb50297a1d2e9')
assert(response.status_code == 200)
print(response.json())

