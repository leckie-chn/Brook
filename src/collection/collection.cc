

//---------------------------------------------------------------------------------------------
// Implementation of kv_store broadcast:
//---------------------------------------------------------------------------------------------
void KVStoreBroadcast() {

    LOG(INFO) << "Start broadcast model ...";
    // Initialize a new KV_Iterator
    scoped_ptr<KV_Iterator> kv_store_iter;
    kv_store_iter.reset(new kv_store);
    kv_store.Initialzie(Get_KV_Store().get());
    LOG(INFO) << "Creating kv_store_iter succeeded ...";

    string key, value;
    LOG(INFO) << "Start reading key value pair from kv_store.";
    // Reading key, value in the specified kv_store.
    while (true) {
        if (!kv_store_iter.hasNext(key, value)) {
            break;
        }

    }

}