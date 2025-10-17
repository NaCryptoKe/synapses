# Synapses — Local P2P Sync (dev)

## Quick start (dev)
1. Create virtualenv & install:
   python -m venv .venv
   .venv\Scripts\Activate.ps1   # Windows PowerShell
   pip install -r requirements.txt

2. Start server (example):
   uvicorn server:app --host 192.168.8.146 --port 12355

3. Start announcer:
   python announcer.py

4. Start client:
   python client.py

## Hosts/Ports used in tests
- Example dev host: 192.168.8.146
- Example service port: 12355
- Token endpoint: POST /auth/token
- Handshake endpoints: GET /handshake/start, POST /handshake/complete
- Metadata endpoint: POST /update_metadata

## Repo checklist (Day 1)
- [ ] Locate `synapses.key`
- [ ] Locate `encrypt.py` / `encrypt` module
- [ ] Locate FastAPI endpoints (server.py / auth routes)
- [ ] Locate Zeroconf announcer (announcer.py)
- [ ] Locate Zeroconf client (client.py)
- [ ] Set synapses.key permissions (see notes)
- [ ] Add this README and update hosts/ports if changed

## Notes
- Keys should be persisted and permission-restricted.
- Zeroconf discovery is not secure — always verify tokens before trusting devices.
